open QCheck_alcotest
open Pa5__Lib

(* ------------------------------------------------------------ *)
(*  LOGGING (overwrite each run)                                *)
(* ------------------------------------------------------------ *)

let () =
  if not (Sys.file_exists "test") then Unix.mkdir "test" 0o755

let log_file = "test/llm_debug_pa5.log"

let log_buffer = Buffer.create 64_000
let log (s : string) = Buffer.add_string log_buffer s
let logf fmt = Printf.ksprintf (fun s -> Buffer.add_string log_buffer s) fmt

let flush_log () =
  let oc = open_out log_file in
  Buffer.output_buffer oc log_buffer;
  close_out oc

let () =
  let ts = Unix.gmtime (Unix.time ()) in
  logf "=== LLM Test Log (PA5 Scheme1 Parser + Interpreter) ===\n";
  logf "UTC %04d-%02d-%02d %02d:%02d:%02d\n\n"
    (ts.tm_year + 1900) (ts.tm_mon + 1) ts.tm_mday ts.tm_hour ts.tm_min ts.tm_sec;
  flush_log ()

(* ------------------------------------------------------------ *)
(*  Utilities                                                   *)
(* ------------------------------------------------------------ *)

let strip_fences (s : string) : string =
  let open Str in
  s
  |> global_replace (regexp {|```[jJ][sS][oO][nN]|}) ""
  |> global_replace (regexp {|```|}) ""
  |> String.trim

let parse_llm_cases (txt : string) : (string * string * string) list =
  let open Yojson.Basic.Util in
  try
    Yojson.Basic.from_string txt
    |> to_list
    |> List.filter_map (fun j ->
           let name =
             j |> member "name" |> to_string_option
             |> Option.value ~default:"llm_case"
           in
           let input = j |> member "input" |> to_string_option in
           let expect = j |> member "expected" |> to_string_option in
           match (input, expect) with
           | Some p, Some e -> Some (name, p, e)
           | _ -> None)
  with _ -> []

(* ------------------------------------------------------------ *)
(*  LLM API connector                                           *)
(* ------------------------------------------------------------ *)

let fetch_with (prompt : string) : (string * string * string) list =
  match (Sys.getenv_opt "GEMINI_API_KEY", Sys.getenv_opt "OPENAI_API_KEY") with
  | Some gkey, _ ->
      let raw = Llm_client.call_gemini_api gkey prompt in
      begin
        match Llm_client.extract_text_from_gemini raw with
        | Some txt -> parse_llm_cases (strip_fences txt)
        | None -> (
            match Sys.getenv_opt "OPENAI_API_KEY" with
            | Some okey ->
                let raw2 = Llm_client.call_openai_api okey prompt in
                begin
                  match Llm_client.extract_text_from_openai raw2 with
                  | Some t -> parse_llm_cases (strip_fences t)
                  | None -> []
                end
            | None -> [])
      end
  | None, Some okey ->
      let raw = Llm_client.call_openai_api okey prompt in
      begin
        match Llm_client.extract_text_from_openai raw with
        | Some t -> parse_llm_cases (strip_fences t)
        | None -> []
      end
  | _ -> []

(* ------------------------------------------------------------ *)
(*  Prompts for both parts                                      *)
(* ------------------------------------------------------------ *)

let parser_prompt =
  "Generate 5 JSON test cases for testing a Scheme1 parser. \
   Scheme1 is a small Scheme-like language with S-expression syntax. \
   Each item MUST be an object with fields: \
   {\"name\": string, \"input\": string, \"expected\": string}. \
   - The input must be a Scheme1 expression written in varied styles \
     (different spacing, nesting, or symbol placement). \
   - The expected field must describe, in plain English, the structure of the parsed AST \
     (for example: \"binary add of 3 and 4\", \"let binding x=5 used in (+ x 2)\", \
      \"application of (fun x (+ x 1)) to 3\"). \
   - Use only these constructs: numbers, booleans, identifiers, (not e), (neg e), \
     (+ e1 e2), (- e1 e2), (* e1 e2), (/ e1 e2), (= e1 e2), (< e1 e2), \
     (and e1 e2), (or e1 e2), (if e1 e2 e3), (let x e2 e3), (fun x e), and (e1 e2). \
   Respond ONLY with a JSON array of 5 test cases and nothing else."

let interp_prompt =
  "Generate 5 JSON test cases for testing a Scheme1 interpreter. \
   Each item MUST be an object with fields: \
   {\"name\": string, \"input\": string, \"expected\": string}. \
   - The input must be a valid Scheme1 expression using these constructs \
     (+, -, *, /, not, neg, =, <, and, or, if, let, fun, application), \
     written in diverse styles and spacing. \
   - The expected field must be the final computed numeric or boolean result as a string \
     (for example: \"7\", \"false\", \"3.5\"). \
   - Include a mix of simple arithmetic, nested expressions, multiple let-bindings, \
     and conditionals that test both true and false branches, as well as functions \
     and function application. \
   Respond ONLY with a JSON array of 5 test cases and nothing else."

(* ------------------------------------------------------------ *)
(*  Fetch both sets and log                                     *)
(* ------------------------------------------------------------ *)

let fetch_pa5_parser_cases () =
  let cs = fetch_with parser_prompt in
  let cs =
    if cs = [] then (
      logf "[LLM] Loaded 0 parser cases (fallback synthetic)\n";
      [
        ("simple_add", "(+ 3 4)", "binary add of 3 and 4");
        ("let_then_use", "(let x 5 (+ x 2))",
         "let binding x=5 used in (+ x 2)");
        ("fun_id", "(fun x x)",
         "anonymous function taking x and returning x");
        ("simple_app", "((fun x (+ x 1)) 3)",
         "application of (fun x (+ x 1)) to 3");
        ("and_or_combo", "(and (or false true) true)",
         "and of (or false true) with true");
      ]
    ) else cs
  in
  logf "[LLM] Loaded %d parser cases\n" (List.length cs);
  flush_log ();
  cs

let fetch_pa5_interpreter_cases () =
  let cs = fetch_with interp_prompt in
  logf "[LLM] Loaded %d interpreter cases\n" (List.length cs);
  flush_log ();
  cs

(* ------------------------------------------------------------ *)
(*  Runners                                                     *)
(* ------------------------------------------------------------ *)

let run_parser (name, prog, expected_str) : bool =
  let parsed = Pa5__Lib.parse prog in
  logf "[PARSER] %s\n  input=%s\n  expected_AST=%s\n" name prog expected_str;
  (match parsed with
   | Ok _ ->
       logf "  result=Ok(...AST built...)  success=true\n\n"
   | Error msg ->
       logf "  ERROR=%s\n\n" msg);
  flush_log ();
  true (* always succeed; logging only *)

let run_interpreter (name, prog, expected_str) : bool =
  let actual = Pa5__Lib.run prog in
  logf "[INTERP] %s\n  input=%s\n  expected=%s\n" name prog expected_str;
  (match actual with
   | Ok (VFloat f) ->
       let s = Printf.sprintf "%.3f" f in
       logf "  actual=VFloat %.3f  match=%b\n\n" f (s = expected_str)
   | Ok (VBool b) ->
       let s = if b then "true" else "false" in
       logf "  actual=VBool %b  match=%b\n\n" b (s = expected_str)
   | Ok (VClos _) ->
       (* Should not happen if the prompt is obeyed, but be robust. *)
       logf "  actual=VClos <fun>  (no numeric/boolean expected)\n\n"
   | Error msg ->
       logf "  ERROR=%s\n\n" msg);
  flush_log ();
  true (* always succeed; logging only *)

(* ------------------------------------------------------------ *)
(*  Convert to QCheck / Alcotest                                *)
(* ------------------------------------------------------------ *)

let to_parser_case (name, prog, expect) =
  to_alcotest
  @@ QCheck.Test.make
       ~name:("LLM_PA5_Parser - " ^ name)
       ~count:1
       QCheck.unit
       (fun () ->
         ignore (run_parser (name, prog, expect));
         true)

let to_interpreter_case (name, prog, expect) =
  to_alcotest
  @@ QCheck.Test.make
       ~name:("LLM_PA5_Interp - " ^ name)
       ~count:1
       QCheck.unit
       (fun () ->
         ignore (run_interpreter (name, prog, expect));
         true)

let llm_pa5_tests =
  let parser_cases =
    fetch_pa5_parser_cases () |> List.map to_parser_case
  in
  let interp_cases =
    fetch_pa5_interpreter_cases () |> List.map to_interpreter_case
  in
  parser_cases @ interp_cases
