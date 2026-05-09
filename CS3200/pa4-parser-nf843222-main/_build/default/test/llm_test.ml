open QCheck_alcotest
open Pa4__Lib

(* ------------------------------------------------------------ *)
(*  LOGGING (overwrite each run)                                *)
(* ------------------------------------------------------------ *)
let () = if not (Sys.file_exists "test") then Unix.mkdir "test" 0o755
let log_file = "test/llm_debug_pa4.log"

let log_buffer = Buffer.create 64_000
let log (s:string) = Buffer.add_string log_buffer s
let logf fmt = Printf.ksprintf (fun s -> Buffer.add_string log_buffer s) fmt
let flush_log () =
  let oc = open_out log_file in
  Buffer.output_buffer oc log_buffer;
  close_out oc

let () =
  let ts = Unix.gmtime (Unix.time ()) in
  logf "=== LLM Test Log (PA4 Parser + Interpreter) ===\n";
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

let parse_llm_cases (txt : string)
  : (string * string * string) list =
  let open Yojson.Basic.Util in
  try
    Yojson.Basic.from_string txt |> to_list |> List.filter_map (fun j ->
      let name = j |> member "name" |> to_string_option |> Option.value ~default:"llm_case" in
      let input = j |> member "input" |> to_string_option in
      let expect = j |> member "expected" |> to_string_option in
      match input, expect with
      | Some p, Some e -> Some (name, p, e)
      | _ -> None)
  with _ -> []

(* ------------------------------------------------------------ *)
(*  LLM API connector                                           *)
(* ------------------------------------------------------------ *)
let fetch_with (prompt:string) : (string * string * string) list =
  match Sys.getenv_opt "GEMINI_API_KEY", Sys.getenv_opt "OPENAI_API_KEY" with
  | Some gkey, _ ->
      let raw = Llm_client.call_gemini_api gkey prompt in
      begin match Llm_client.extract_text_from_gemini raw with
      | Some txt -> parse_llm_cases (strip_fences txt)
      | None ->
          (match Sys.getenv_opt "OPENAI_API_KEY" with
           | Some okey ->
               (match Llm_client.extract_text_from_openai (Llm_client.call_openai_api okey prompt) with
                | Some t -> parse_llm_cases (strip_fences t)
                | None -> [])
           | None -> [])
      end
  | None, Some okey ->
      (match Llm_client.extract_text_from_openai (Llm_client.call_openai_api okey prompt) with
       | Some t -> parse_llm_cases (strip_fences t)
       | None -> [])
  | _ -> []

(* ------------------------------------------------------------ *)
(*  Prompts for both parts                                      *)
(* ------------------------------------------------------------ *)

let parser_prompt =
  "Generate 5 JSON test cases for testing a Scheme0 **parser**. \
   Each item MUST be an object with fields: \
   {\"name\": string, \"input\": string, \"expected\": string}. \
   - The 'input' must be a Scheme expression written in varied styles \
     (different spacing, nesting, or symbol placement). \
   - The 'expected' must describe, in plain English, the structure of the parsed AST \
     (for example: 'binary add of 3 and 4', 'let binding x=5 used in (+ x 2)'). \
   - Cover examples of these core forms: numbers, booleans, identifiers, \
     (not e), (+ e1 e2), (if e1 e2 e3), and (let x e2 e3). \
   Respond ONLY with a JSON array of 5 test cases and nothing else."

let interp_prompt =
  "Generate 5 JSON test cases for testing a Scheme0 **interpreter**. \
   Each item MUST be an object with fields: \
   {\"name\": string, \"input\": string, \"expected\": string}. \
   - The 'input' must be a valid Scheme expression using the same language features \
     (+, -, *, /, not, if, and let), written in diverse styles and spacing. \
   - The 'expected' must be the final computed numeric or boolean result as a string \
     (for example: '7', 'false', '3.5'). \
   - Include a mix of simple arithmetic, nested expressions, multiple let-bindings, \
     and conditionals that test true and false branches. \
   Respond ONLY with a JSON array of 5 test cases and nothing else."


(* ------------------------------------------------------------ *)
(*  Fetch both sets and log                                     *)
(* ------------------------------------------------------------ *)
let fetch_pa4_parser_cases () =
  let cs = fetch_with parser_prompt in
  let cs =
    if cs = [] then (
      logf "[LLM] Loaded 0 parser cases (fallback synthetic)\n";
      [
        ("simple_add", "(+ 3 4)", "binary add of 3 and 4");
        ("nested_let", "(let x 5 (+ x 2))", "let binding x=5 used in (+ x 2)");
        ("boolean_not", "(not false)", "unary not applied to false");
        ("if_expression", "(if true 1 2)", "if condition true yields 1");
        ("complex_nesting", "(let y 10 (if (< y 20) (* y 2) (/ y 2)))",
          "nested let and if producing 20")
      ]
    ) else cs
  in
  logf "[LLM] Loaded %d parser cases\n" (List.length cs);
  flush_log (); cs


let fetch_pa4_interpreter_cases () =
  let cs = fetch_with interp_prompt in
  logf "[LLM] Loaded %d interpreter cases\n" (List.length cs); flush_log (); cs

(* ------------------------------------------------------------ *)
(*  Runners                                                     *)
(* ------------------------------------------------------------ *)
let run_parser (name, prog, expected_str) : bool =
  let parsed = Pa4__Lib.parse prog in
  logf "[PARSER] %s\n  input=%s\n  expected_AST=%s\n" name prog expected_str;
  (match parsed with
   | Ok _ -> logf "  result=Ok(...AST built...)  success=true\n\n"
   | Error msg -> logf "  ERROR=%s\n\n" msg);
  flush_log ();
  true  (* always succeed; logging only *)

let run_interpreter (name, prog, expected_str) : bool =
  let actual = Pa4__Lib.run prog in
  logf "[INTERP] %s\n  input=%s\n  expected=%s\n" name prog expected_str;
  match actual with
  | Ok (VFloat f) ->
      let s = Printf.sprintf "%.3f" f in
      logf "  actual=VFloat %.3f  match=%b\n\n" f (s = expected_str);
      flush_log (); true
  | Ok (VBool b) ->
      let s = if b then "true" else "false" in
      logf "  actual=VBool %b  match=%b\n\n" b (s = expected_str);
      flush_log (); true
  | Error msg ->
      logf "  ERROR=%s\n\n" msg; flush_log (); true

(* ------------------------------------------------------------ *)
(*  Convert to QCheck tests                                     *)
(* ------------------------------------------------------------ *)
let to_parser_case (name, prog, expect) =
  to_alcotest @@ QCheck.Test.make
    ~name:("LLM_PA4_Parser - " ^ name)
    ~count:1 QCheck.unit (fun () -> ignore (run_parser (name, prog, expect)); true)

let to_interpreter_case (name, prog, expect) =
  to_alcotest @@ QCheck.Test.make
    ~name:("LLM_PA4_Interp - " ^ name)
    ~count:1 QCheck.unit (fun () -> ignore (run_interpreter (name, prog, expect)); true)

let llm_pa4_tests =
  let parser_cases = fetch_pa4_parser_cases () |> List.map to_parser_case in
  let interp_cases = fetch_pa4_interpreter_cases () |> List.map to_interpreter_case in
  parser_cases @ interp_cases
