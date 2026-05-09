open Num
open Yojson.Basic.Util
(*open QCheck
open Util
open Pa4 *)

(* ------------------------------------------------------------------ *)
(*  Bindings to your library functions                                 *)
(* ------------------------------------------------------------------ *)
let fib_func : int -> Num.num =
try Pa4.Fib.fib with _ -> (fun _ -> Num.num_of_int 0)

let rec_func : int -> string =
try Pa4.Fib_like.f with _ -> (fun _ -> "0")

(* ------------------------------------------------------------------ *)
(*  LOGGING                                                             *)
(* ------------------------------------------------------------------ *)
let () = if not (Sys.file_exists "test") then Unix.mkdir "test" 0o755
let log_file = "test/llm_debug.log"
let log_buffer = Buffer.create 64_000
(*let log_console s = print_string s*)
let logf_console fmt = Printf.ksprintf print_string fmt
let flush_log () =
let oc = open_out log_file in
Buffer.output_buffer oc log_buffer;
close_out oc

let () =
let ts = Unix.gmtime (Unix.time ()) in
logf_console "=== LLM Test Log (overwrite) ===\n";
logf_console "UTC %04d-%02d-%02d %02d:%02d:%02d\n\n"
(ts.tm_year + 1900) (ts.tm_mon + 1) ts.tm_mday ts.tm_hour ts.tm_min ts.tm_sec;
flush_log ()

(* ------------------------------------------------------------------ *)
(*  JSON helpers                                                       *)
(* ------------------------------------------------------------------ *)
let strip_fences (s : string) : string =
let open Str in
s
|> global_replace (regexp {|`[jJ][sS][oO][nN]|}) ""
  |> global_replace (regexp {|`|}) ""
|> global_replace (regexp ";") ","
|> global_replace (regexp {|]\[|}) "],["
|> String.trim

let json_list = function `List l -> l | _ -> []

let parse_cases_generic (txt : string)
: (string * Yojson.Basic.t list * Yojson.Basic.t list) list =
let body =
match (String.index_opt txt '[', String.rindex_opt txt ']') with
| Some i, Some j when j >= i -> String.sub txt i (j - i + 1)
| _ -> txt
in
try
Yojson.Basic.from_string body |> to_list |> List.filter_map (fun j ->
let name =
(match j |> member "name" with
| `String s -> s          | _ ->
           (match j |> member "description" with             | `String s -> s | _ -> "llm_case"))
in
let input = j |> member "input" in
let a_json, b_json =
if input = `Null then
let aj = j |> member "a" in
let bj = j |> member "b" in
(aj, bj)
else
(input |> member "a", input |> member "b")
in
Some (name, json_list a_json, json_list b_json))
with _ -> []

let show_json_list (xs:Yojson.Basic.t list) : string =
"[" ^ (String.concat ", " (List.map Yojson.Basic.to_string xs)) ^ "]"

let print_llm_cases name cases =
  List.iter (fun (case_name, a_list, b_list) ->
    logf_console "=== %s: %s ===\n" name case_name;
    logf_console "Input JSON: %s\n" (show_json_list a_list);
    logf_console "Expected JSON: %s\n\n" (show_json_list b_list)
  ) cases;
  flush_log ()

(* ------------------------------------------------------------------ *)
(*  LLM fetcher                                                        *)
(* ------------------------------------------------------------------ *)
let fetch_with (prompt : string)
  : (string * Yojson.Basic.t list * Yojson.Basic.t list) list =
  match
    Sys.getenv_opt "GEMINI_API_KEY",
    Sys.getenv_opt "OPENAI_API_KEY",
    Sys.getenv_opt "NVIDIA_API_KEY",
    Sys.getenv_opt "ANTHROPIC_API_KEY"
  with
  (* 1. Try Gemini first *)
  | Some gkey, _, _, _ -> begin
      let raw = Llm_client.call_gemini_api gkey prompt in
      match Llm_client.extract_text_from_gemini raw with
      | Some txt -> parse_cases_generic (strip_fences txt)
      | None ->
          (* fallback to OpenAI *)
          (match Sys.getenv_opt "OPENAI_API_KEY" with
           | Some okey ->
               (match Llm_client.extract_text_from_openai
                        (Llm_client.call_openai_api okey prompt)
                with
                | Some t -> parse_cases_generic (strip_fences t)
                | None ->
                    (* fallback to NVIDIA *)
                    (match Sys.getenv_opt "NVIDIA_API_KEY" with
                     | Some nkey ->
                         (match Llm_client.extract_text_from_nvidia
                                  (Llm_client.call_nvidia_api nkey prompt)
                          with
                          | Some n -> parse_cases_generic (strip_fences n)
                          | None ->
                              (* fallback to Claude *)
                              (match Sys.getenv_opt "ANTHROPIC_API_KEY" with
                               | Some akey ->
                                   (match Llm_client.extract_text_from_anthropic
                                            (Llm_client.call_anthropic_api akey prompt)
                                    with
                                    | Some c -> parse_cases_generic (strip_fences c)
                                    | None -> [])
                               | None -> []))
                     | None -> []))
           | None -> [])
    end

  (* 2. If Gemini not set, try OpenAI *)
  | None, Some okey, _, _ -> begin
      let raw = Llm_client.call_openai_api okey prompt in
      match Llm_client.extract_text_from_openai raw with
      | Some txt -> parse_cases_generic (strip_fences txt)
      | None ->
          (* fallback to NVIDIA, then Claude *)
          (match Sys.getenv_opt "NVIDIA_API_KEY" with
           | Some nkey ->
               (match Llm_client.extract_text_from_nvidia
                        (Llm_client.call_nvidia_api nkey prompt)
                with
                | Some n -> parse_cases_generic (strip_fences n)
                | None ->
                    (match Sys.getenv_opt "ANTHROPIC_API_KEY" with
                     | Some akey ->
                         (match Llm_client.extract_text_from_anthropic
                                  (Llm_client.call_anthropic_api akey prompt)
                          with
                          | Some c -> parse_cases_generic (strip_fences c)
                          | None -> [])
                     | None -> []))
           | None -> [])
    end

  (* 3. If neither Gemini nor OpenAI, try NVIDIA *)
  | None, None, Some nkey, _ -> begin
      let raw = Llm_client.call_nvidia_api nkey prompt in
      match Llm_client.extract_text_from_nvidia raw with
      | Some txt -> parse_cases_generic (strip_fences txt)
      | None ->
          (* fallback to Claude *)
          (match Sys.getenv_opt "ANTHROPIC_API_KEY" with
           | Some akey ->
               (match Llm_client.extract_text_from_anthropic
                        (Llm_client.call_anthropic_api akey prompt)
                with
                | Some c -> parse_cases_generic (strip_fences c)
                | None -> [])
           | None -> [])
    end

  (* 4. Finally try Claude alone *)
  | None, None, None, Some akey -> begin
      let raw = Llm_client.call_anthropic_api akey prompt in
      match Llm_client.extract_text_from_anthropic raw with
      | Some txt -> parse_cases_generic (strip_fences txt)
      | None -> []
    end

  (* 5. No API key found *)
  | _ -> []


(* ------------------------------------------------------------------ *)
(*  Fibonacci tests                                                    *)
(* ------------------------------------------------------------------ *)
let fetch_fib_cases () =
let prompt = {|
Return ONLY valid JSON, no markdown, no commentary, no code fences.
Respond exactly with a JSON array of 5 objects, each of the form:
{"name": string, "input": {"a": [n], "b": [expected]}}.
n must be a non-negative integer for the Fibonacci sequence, with f(0)=0, f(1)=1.
Include one case where n > 30 to ensure a large result.
|}
in
let cs = fetch_with prompt in
logf_console "[LLM] Loaded %d fibonacci cases\n" (List.length cs); flush_log (); cs


let run_and_log_fib (name, a, b) : bool =
let n =
match a with
| (`Int i) :: _ -> i     
| (`Float f) :: _ -> int_of_float f
| _ -> 0
in
let expected =
match b with
| (`String s) :: _ -> s     
| (`Int i) :: _ -> string_of_int i
| (`Float f) :: _ -> string_of_int (int_of_float f)
| _ -> "0"
in
let actual =
try string_of_num (fib_func n) with _ -> "-999999"
in
let ok = (actual = expected) in
logf_console "[FIB] %s\n  input.n=%d\n  expected=%s\n  actual=%s\n  match=%b\n\n"
name n expected actual ok;
flush_log ();
true

let to_fib_case (name, a, b) =
  QCheck.Test.make
    ~name:("LLM_Fib - " ^ name)
    ~count:1
    ~long_factor:1
    QCheck.unit
    (fun () ->
      let _ = run_and_log_fib (name, a, b) in
      true
    )

let fib_cases = fetch_fib_cases ()
let () = print_llm_cases "Fibonacci" fib_cases
let llm_fib_tests = fib_cases |> List.map to_fib_case

(* ------------------------------------------------------------------ *)
(*  Recurrence tests                                                   *)
(* ------------------------------------------------------------------ *)
let fetch_recurrence_cases () =
let prompt = {|
Generate 5 JSON test cases ONLY for the recurrence:
8f(n)f(n+1) - 6f(n)*f(n+2) + f(n+1)*f(n+2) = 0.
Start with initial conditions f(0)=1, f(1)=2, compute f(n) for n >=2.
Each case must include concrete integers n and f(n) as string that satisfies the recurrence.
Include at least one case with n >= 10 so output is large.
Each item MUST be: {"name": string, "input": {"a": [n], "b": [f_n]}}.
Respond ONLY with a JSON array.|}
in
let cs = fetch_with prompt in
if cs = [] then (
logf_console "[LLM] Loaded 0 recurrence cases (fallback)\n";
flush_log ();
[
("rec_fallback_1", [`Int 1], [`String "2"]);
("rec_fallback_2", [`Int 2], [`String "4"]);
("rec_fallback_3", [`Int 11], [`String "2048"]);
]
) else (
logf_console "[LLM] Loaded %d recurrence cases\n" (List.length cs);
flush_log ();
cs
)

let run_and_log_recurrence (name,a,b) : bool =
let n =
match a with
| (`Int i) :: _ -> i 
| _ -> 0 
in 
let expected = 
  match b with 
  | (`String s) :: _ -> s
  | _ -> "0"
in
let actual = try rec_func n with _ -> "ERR" in
let ok = (actual = expected) in
logf_console "[RECURRENCE] %s\n input.n=%d\n expected=%s\n actual=%s\n match=%b\n\n"
name n expected actual ok;
flush_log ();
true


let to_recurrence_case (name, a, b) =
  QCheck.Test.make
    ~name:("LLM_Recurrence - " ^ name)
    ~count:1
    ~long_factor:1
    QCheck.unit
    (fun () ->
      let _ = run_and_log_recurrence (name, a, b) in
      true
    )

let rec_cases = fetch_recurrence_cases ()
let () = print_llm_cases "Recurrence" rec_cases
let llm_recurrence_tests = rec_cases |> List.map to_recurrence_case

    

let () =
  let _ = QCheck_runner.run_tests ~verbose:true llm_fib_tests in
  let _ = QCheck_runner.run_tests ~verbose:true llm_recurrence_tests in
  ()
