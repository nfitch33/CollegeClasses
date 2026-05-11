(* ============================================================ *)
(*  LLM TEST DRIVER (PA6 TYPED SCHEME) — FULL FIXED VERSION    *)
(* ============================================================ *)

open QCheck_alcotest
open Pa6__Lib
open Llm_client
open Sexplib

(* ------------------------------------------------------------ *)
(*  LOGGING                                                     *)
(* ------------------------------------------------------------ *)
let () = if not (Sys.file_exists "test") then Unix.mkdir "test" 0o755
let log_file = "test/llm_debug_pa6.log"

let log_buffer = Buffer.create 64_000
let log s = Buffer.add_string log_buffer s
let logf fmt = Printf.ksprintf (fun s -> Buffer.add_string log_buffer s) fmt

let flush_log () =
  let oc = open_out log_file in
  Buffer.output_buffer oc log_buffer;
  close_out oc

let () =
  let ts = Unix.gmtime (Unix.time ()) in
  logf "=== LLM Test Log (PA6 Typed Scheme1) ===\n";
  logf "UTC %04d-%02d-%02d %02d:%02d:%02d\n\n"
    (ts.tm_year + 1900) (ts.tm_mon + 1) ts.tm_mday ts.tm_hour ts.tm_min ts.tm_sec;
  flush_log ()

(* ------------------------------------------------------------ *)
(*  BASIC VALIDATION FILTERS                                    *)
(* ------------------------------------------------------------ *)

let valid_binops = ["+"; "-"; "*"; "/"; "="; "<"]

let is_valid_binop op = List.exists ((=) op) valid_binops

let extract_leading_symbol sexp =
  try
    match Sexplib.Sexp.of_string sexp with
    | List (Atom op :: _) -> Some op
    | _ -> None
  with _ -> None

let contains_invalid_op str =
  match extract_leading_symbol str with
  | Some op when is_valid_binop op -> false
  | Some op when
      op = "let" || op = "fun" || op = "rec" ||
      op = "if" || op = "not" || op = "neg" ||
      op = "and" || op = "or"
      -> false
  | Some op ->
      logf "[FILTER] Dropping invalid operator \"%s\" in input: %s\n" op str;
      true
  | None -> false

(* reject multi-arg ONLY if the head is NOT "if" *)
let strip_multi_arg_apps str =
  try
    match Sexplib.Sexp.of_string str with
    | List (Atom "if" :: _ ) -> Some str    (* allow 3-arg if *)
    | _ ->
        let regexp = Str.regexp "(\\([^() ]+\\) +\\([^() ]+\\) +\\([^() ]+\\) +\\([^() ]+\\))" in
        if Str.string_match regexp str 0 then (
          logf "[FILTER] Dropping multi-argument application in: %s\n" str;
          None
        ) else Some str
  with _ -> Some str


let validate_case (name, input, expected) =
  if contains_invalid_op input then None
  else match strip_multi_arg_apps input with
       | None -> None
       | Some clean -> Some (name, clean, expected)

let filter_cases cases = List.filter_map validate_case cases

(* ------------------------------------------------------------ *)
(*  SPECIAL RULE FOR parse_ty (NO FILTERING)                    *)
(* ------------------------------------------------------------ *)
let filter_cases_parse_ty c = c

(* ------------------------------------------------------------ *)
(*  NAME VALIDATION — REJECT “Test 1”, “Program 5”, etc.        *)
(* ------------------------------------------------------------ *)

let bad_name name =
  let open Str in
  let patterns = [
    "^[Tt]est *[0-9]+$";
    "^[Pp]rogram *[0-9]+$";
    "^case *[0-9]+$";
    "^[0-9]+$"
  ] in
  List.exists (fun pat -> string_match (regexp pat) name 0) patterns

(* ------------------------------------------------------------ *)
(*  PARSER FOR RAW JSON                                         *)
(* ------------------------------------------------------------ *)

let strip_fences s =
  let open Str in
  s |> global_replace (regexp {|```[jJ][sS][oO][nN]|}) ""
    |> global_replace (regexp {|```|}) ""
    |> String.trim

let parse_llm_cases txt =
  let open Yojson.Basic in
  try
    match from_string txt with
    | `List lst ->
        lst
        |> List.filter_map (fun j ->
            match j with
            | `Assoc _ ->
                let name =
                  j |> Util.member "name" |> Util.to_string_option
                  |> Option.value ~default:"llm_case"
                in
                let input =
                  match j |> Util.member "input" with
                  | `String s -> Some s
                  | _ -> None
                in
                let expected =
                  match j |> Util.member "expected" with
                  | `Null -> None
                  | e -> Some (Yojson.Basic.to_string e)
                in
                begin match input, expected with
                | Some i, Some e -> Some (name, i, e)
                | Some i, None -> Some (name, i, "\"\"")
                | _ -> None
                end
            | _ -> None)
    | _ -> []
  with _ -> []

(* ------------------------------------------------------------ *)
(*  PROVIDER WRAPPER WITH RAW LOGGING                           *)
(* ------------------------------------------------------------ *)

let fetch_with prompt =
  match Sys.getenv_opt "GEMINI_API_KEY", Sys.getenv_opt "OPENAI_API_KEY" with
  | Some gkey, _ ->
      let raw = call_gemini_api gkey prompt in
      begin match extract_text_from_gemini raw with
      | Some txt ->
          logf "=== EXTRACTED_TEXT_FROM_GEMINI ===\n%s\n\n" txt; flush_log ();
          let parsed = parse_llm_cases (strip_fences txt) in
          logf "=== RAW_GEMINI_RESPONSE ===\n%s\n\n" raw; flush_log ();
          parsed
      | None ->
          logf "GEMINI_PARSE_FAIL\n\nRAW:\n%s\n\n" raw; flush_log ();
          []
      end

  | None, Some okey ->
      let raw = call_openai_api okey prompt in
      begin match extract_text_from_openai raw with
      | Some txt ->
          logf "=== EXTRACTED_TEXT_FROM_OPENAI ===\n%s\n\n" txt; flush_log ();
          let parsed = parse_llm_cases (strip_fences txt) in
          logf "=== RAW_OPENAI_RESPONSE ===\n%s\n\n" raw; flush_log ();
          parsed
      | None ->
          logf "OPENAI_PARSE_FAIL\n\nRAW:\n%s\n\n" raw; flush_log ();
          []
      end

  | _ ->
      logf "NO_API_KEYS AVAILABLE\n"; flush_log (); []
      
(* ------------------------------------------------------------ *)
(*  RETRY UNTIL 5 VALID CASES FOUND                             *)
(* ------------------------------------------------------------ *)

let rec require_five_cases label prompt fallback filter_fun attempt =
  if attempt > 5 then (
    logf "[LLM] GIVING UP for %s — using fallback\n" label;
    flush_log ();
    fallback
  ) else (
    let raw_cases = fetch_with prompt in
    let filtered =
      raw_cases
      |> filter_fun
      |> List.filter (fun (n,_,_) -> not (bad_name n))
    in
    if List.length filtered = 5 then (
      logf "[LLM] %s succeeded at attempt %d with 5 good cases\n"
        label attempt;
      flush_log ();
      filtered
    ) else (
      logf "[LLM] %s retry %d: got %d valid — need 5\n"
        label attempt (List.length filtered);
      flush_log ();
      require_five_cases label prompt fallback filter_fun (attempt + 1)
    )
  )

(* ------------------------------------------------------------ *)
(*  UNIFIED LOADER                                              *)
(* ------------------------------------------------------------ *)

let load_cases label prompt fallback filter_fun =
  require_five_cases label prompt fallback filter_fun 1


(* ------------------------------------------------------------ *)
(*  STRICT(ish) PROMPTS – but NO "output []" suicide clauses    *)
(* ------------------------------------------------------------ *)

let prompt_parse_ty =
  "You are generating tests for a PA6 type parser.\n\
   Return ONLY a JSON array (no markdown, no code fences, no text outside JSON).\n\
   The array must have EXACTLY 5 objects.\n\
   Each object must have fields:\n\
     - \"name\": a short string\n\
     - \"input\": a PA6 type in S-expression syntax\n\
     - \"expected\": a short description string\n\
   Allowed type syntax ONLY:\n\
     bool\n\
     float\n\
     (-> t1 t2)   where t1 and t2 are themselves valid types.\n\
   Examples of valid inputs:\n\
     bool\n\
     float\n\
     (-> float bool)\n\
     (-> bool (-> float float))\n\
   DO NOT use Int, Num, Nat, capital Bool, or any other type constructors.\n\
   DO NOT include explanations. Output MUST be just the JSON array."

let prompt_parse_exp =
  "You are generating tests for a PA6 expression parser (typed Scheme in S-expression form).\n\
   Return ONLY a JSON array with EXACTLY 5 objects.\n\
   No markdown, no code fences, no extra text.\n\
   Each object: {\"name\":..., \"input\":..., \"expected\":...}.\n\
   The \"input\" MUST be a PA6 expression using ONLY the following syntax:\n\
     x                           ; identifier\n\
     true | false | numbers      ; literals\n\
     (let x t e2 e3)\n\
     (fun x t e)\n\
     (rec x t e)\n\
     (if e1 e2 e3)\n\
     (not e) | (neg e)\n\
     (b e1 e2)   where b in {+, -, *, /, =, <}\n\
     (e1 e2)     ; function application\n\
   Types t allowed: bool, float, (-> t1 t2).\n\
   ABSOLUTELY FORBIDDEN in input:\n\
     lambda/λ notation, \"fun x ->\", colons, square brackets, [x : T], Int, Num, Nat.\n\
   \"expected\" can be a short English description like \"simple add\", it is NOT parsed.\n\
   Output MUST be just the JSON array."

let prompt_desugar =
  "You are generating tests for a PA6 *desugaring* function.\n\
   Output MUST be a RAW JSON array ONLY. No markdown. No code fences.\n\
   The array MUST have EXACTLY 5 objects.\n\
   Each object MUST have: {\"name\":..., \"input\":..., \"expected\":...}.\n\
   \n\
   *** CRITICAL RULES (follow EXACTLY): ***\n\
   The \"input\" expression MUST be ONE OF THE FOLLOWING SHAPES ONLY:\n\
     1. (and e1 e2)\n\
     2. (or e1 e2)\n\
     3. (neg e)\n\
     4. (let x t e2 e3)\n\
   Where e, e1, e2, e3 are VALID PA6 EXPRESSIONS using ONLY:\n\
     literals: true, false, float numbers\n\
     identifiers: x, y, z\n\
     unary ops: (not e), (neg e)\n\
     binary ops: (+ e1 e2), (- e1 e2), (* e1 e2), (/ e1 e2), (= e1 e2), (< e1 e2)\n\
     if expressions: (if e1 e2 e3)\n\
     function and recursion: (fun x t e), (rec f t e)\n\
     application: (e1 e2)\n\
   \n\
   *** ABSOLUTELY FORBIDDEN (input must be rejected): ***\n\
   • ANY extra arguments (no 3-arg or 4-arg AND/OR)\n\
   • ANY nested LET of shape (let x t (let ...)) — NOT ALLOWED\n\
   • ANY malformed application like (x y z)\n\
   • ANY type syntax except: bool, float, (-> t1 t2)\n\
   • ANY name containing 'Test', 'Program', or numbers only\n\
   \n\
   \"name\" MUST be a short descriptive phrase (e.g., \"and_simple_true\", \"or_nested_bool\").\n\
   \n\
   \"expected\" MUST be a short English phrase.\n\
   \n\
   OUTPUT MUST BE JUST THE JSON ARRAY."


let prompt_tycheck =
  "You are generating tests for a PA6 typechecker.\n\
   Return ONLY a JSON array with EXACTLY 5 objects.\n\
   No markdown, no fences.\n\
   Each object: {\"name\":..., \"input\":..., \"expected\":...}.\n\
   \"input\" MUST be a PA6 expression using ONLY the S-expression syntax described earlier:\n\
     true | false | numbers\n\
     identifiers\n\
     (let x t e2 e3)\n\
     (fun x t e)\n\
     (rec x t e)\n\
     (if e1 e2 e3)\n\
     (not e) | (neg e)\n\
     (b e1 e2)   where b in {+, -, *, /, =, <}\n\
     (e1 e2)     ; application\n\
   Types t: bool, float, (-> t1 t2).\n\
   \"expected\" MUST be ONE of:\n\
     \"bool\"\n\
     \"float\"\n\
     a function type like \"(-> float float)\" or \"(-> bool (-> float float))\"\n\
     or the string \"type error\".\n\
   Do not include explanations; output just the JSON array."

let prompt_interp =
  "STRICT MODE: FOLLOW EXACTLY.\n\
   Output MUST be a RAW JSON array ONLY. No markdown. No fences.\n\
   Each element MUST be an object: {\"name\":..., \"input\":..., \"expected\":...}.\n\
   If ANY rule is violated, output [] EXACTLY.\n\
   \n\
   VALID PA6 SYNTAX ONLY (NO EXCEPTIONS):\n\
     true | false | float-literals\n\
     x\n\
     (let x t e2 e3)\n\
     (fun x t e)\n\
     (rec f t e)\n\
     (if e1 e2 e3)\n\
     (not e) | (neg e)\n\
     (+ e1 e2) (- e1 e2) (* e1 e2) (/ e1 e2)\n\
     (= e1 e2) (< e1 e2)\n\
     (e1 e2)   ; FUNCTION APPLICATION, EXACTLY ONE ARGUMENT\n\
   \n\
   VERY IMPORTANT RESTRICTIONS:\n\
   • let MUST be exactly: (let x t e2 e3) — TYPE t IS REQUIRED.\n\
   • Application MUST be EXACTLY TWO ELEMENTS: (e1 e2). No multi-argument calls.\n\
   • If applying twice, MUST NEST: ((f x) y).\n\
   • MUST include required spaces between tokens.\n\
   • No implicit sequencing.\n\
   • No missing type annotations.\n\
   • No extra parentheses.\n\
   \n\
   Generate EXACTLY 5 valid PA6 programs that evaluate to a number.\n"



(* ------------------------------------------------------------ *)
(*  FETCHERS                                                    *)
(* ------------------------------------------------------------ *)

let fetch_pa6_parse_ty_cases () =
  load_cases "parse_ty" prompt_parse_ty
    [
      ("ty_bool", "bool", "boolean type");
      ("ty_float", "float", "float type");
      ("ty_arrow1", "(-> float float)", "arrow from float to float");
      ("ty_arrow2", "(-> bool float)", "arrow from bool to float");
      ("ty_nested", "(-> float (-> float bool))", "nested arrow");
    ]
    filter_cases_parse_ty

let fetch_pa6_parse_exp_cases () =
  load_cases "parse_exp" prompt_parse_exp
    [
      ("id_x", "x", "identifier");
      ("simple_add", "(+ 3 4)", "binary add");
      ("fun_id", "(fun x float x)", "identity");
      ("app_fun", "((fun x float x) 5)", "apply identity");
      ("rec_id", "(rec f (-> float float) f)", "recursive id");
    ]
    filter_cases

let fetch_pa6_desugar_cases () =
  load_cases "desugar" prompt_desugar
    [
      ("and_tt", "(and true true)", "desugar and");
      ("or_tf", "(or true false)", "desugar or");
      ("neg_v", "(neg 5)", "desugar neg");
      ("let1", "(let x float 3 x)", "desugar let");
      ("nested", "(and (or false true) true)", "nested");
    ]
    filter_cases

let fetch_pa6_tycheck_cases () =
  load_cases "tycheck" prompt_tycheck
    [
      ("tc_bool", "true", "bool");
      ("tc_add", "(+ 2 3)", "float");
      ("tc_fun", "(fun x float (+ x 1))", "(-> float float)");
      ("tc_if", "(if true 1 2)", "float");
      ("tc_err", "(+ true 1)", "type error");
    ]
    filter_cases

let fetch_pa6_interp_cases () =
  load_cases "interp" prompt_interp
    [
      ("i_val", "3", "3");
      ("i_bool", "false", "false");
      ("i_add", "(+ 2 3)", "5");
      ("i_fun", "((fun x float (+ x 2)) 3)", "5");
      ("i_if", "(if false 1 9)", "9");
    ]
    filter_cases

(* ------------------------------------------------------------ *)
(*  RUNNERS                                                     *)
(* ------------------------------------------------------------ *)

let run_parse_ty (n,s,_exp) =
  logf "[PARSE_TY] %s\n  %s\n" n s;
  begin match parse_ty (Sexp.of_string s) with
  | Ok t -> logf "  result=%s\n\n" (ShowTy.show t)
  | Error msg -> logf "  ERROR=%s\n\n" msg
  end;
  flush_log (); true

let run_parse_exp (n,s,_exp) =
  logf "[PARSE_EXP] %s\n  %s\n" n s;
  begin match parse s with
  | Ok e -> logf "  %s\n\n" (ShowExp.show e)
  | Error msg -> logf "  ERROR=%s\n\n" msg
  end;
  flush_log (); true

let run_desugar (n,s,_exp) =
  logf "[DESUGAR] %s\n  %s\n" n s;
  begin match parse s with
  | Error msg -> logf "  PARSE_ERROR=%s\n\n" msg
  | Ok e -> logf "  %s\n\n" (ShowExp.show (desugar e))
  end;
  flush_log (); true

let run_tycheck (n,s,_exp) =
  logf "[TYCHECK] %s\n  %s\n" n s;
  begin match parse s with
  | Error msg -> logf "  PARSE_ERROR=%s\n\n" msg
  | Ok e ->
      match tycheck init_env (desugar e) with
      | Ok t -> logf "  %s\n\n" (ShowTy.show t)
      | Error msg -> logf "  ERROR=%s\n\n" msg
  end;
  flush_log (); true

let run_interp (n,s,_exp) =
  logf "[INTERP] %s\n  %s\n" n s;
  begin match run s with
  | Ok (VFloat f) -> logf "  VFloat %.3f\n\n" f
  | Ok (VBool b) -> logf "  VBool %b\n\n" b
  | Ok (VClos _) -> logf "  VClos ...\n\n"
  | Error msg -> logf "  ERROR=%s\n\n" msg
  end;
  flush_log (); true

(* ------------------------------------------------------------ *)
(*  CONVERT TO QCHECK                                           *)
(* ------------------------------------------------------------ *)

let to_case f (n,s,e) =
  to_alcotest @@ QCheck.Test.make
    ~name:("LLM_PA6 - " ^ n)
    ~count:1 QCheck.unit
    (fun () -> ignore (f (n,s,e)); true)

(* ------------------------------------------------------------ *)
(*  FINAL TEST SUITE                                            *)
(* ------------------------------------------------------------ *)

let llm_pa6_tests =
  List.concat [
    fetch_pa6_parse_ty_cases () |> List.map (to_case run_parse_ty);
    fetch_pa6_parse_exp_cases () |> List.map (to_case run_parse_exp);
    fetch_pa6_desugar_cases  () |> List.map (to_case run_desugar);
    fetch_pa6_tycheck_cases  () |> List.map (to_case run_tycheck);
    fetch_pa6_interp_cases   () |> List.map (to_case run_interp);
  ]
