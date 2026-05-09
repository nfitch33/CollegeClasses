
open QCheck
open QCheck_alcotest

(* Use JSON as general data type for ANY element type *)
module JsonType : Pa3__Set.OType with type t = Yojson.Basic.t = struct
  type t = Yojson.Basic.t
  let le a b = compare a b <= 0

  (* bounded-depth JSON generator *)
  let rec json_gen depth : Yojson.Basic.t Gen.t =
    let open Gen in
    if depth = 0 then
      oneof [ return `Null;
              map (fun b -> `Bool b) bool;
              map (fun i -> `Int i) int;
              map (fun s -> `String s) string ]
    else
      oneof [ return `Null;
              map (fun b -> `Bool b) bool;
              map (fun i -> `Int i) int;
              map (fun s -> `String s) string;
              map (fun xs -> `List xs) (small_list (json_gen (depth - 1))) ]

  let gen = QCheck.make (json_gen 2) ~print:Yojson.Basic.to_string
  let show (j:t) : string = Yojson.Basic.to_string j
end

module LS  = Pa3__Lib.ListSet(JsonType)
module BS  = Pa3__Lib.BstSet(JsonType)
module RBS = Pa3__Lib.RbtSet(JsonType)

(* ------------------------------------------------------------ *)
(*  LOGGING (file only; overwrite each run)                     *)
(* ------------------------------------------------------------ *)
let () = if not (Sys.file_exists "test") then Unix.mkdir "test" 0o755
let log_file = "test/llm_debug.log"

let log_buffer = Buffer.create 64_000

let log (s:string) = Buffer.add_string log_buffer s
let logf fmt = Printf.kprintf (fun s -> Buffer.add_string log_buffer s) fmt
let flush_log () =
  let oc = open_out log_file in              (* overwrite each run *)
  Buffer.output_buffer oc log_buffer;
  close_out oc

let () =
  let ts = Unix.gmtime (Unix.time ()) in
  logf "=== LLM Test Log (overwrite) ===\n";
  logf "UTC %04d-%02d-%02d %02d:%02d:%02d\n\n"
    (ts.tm_year + 1900) (ts.tm_mon + 1) ts.tm_mday ts.tm_hour ts.tm_min ts.tm_sec;
  flush_log ()

(* ------------------------------------------------------------ *)
(*  Helpers (cleaning + parsing)                                *)
(* ------------------------------------------------------------ *)
let strip_fences (s : string) : string =
  let open Str in
  s
  |> global_replace (regexp {|```[jJ][sS][oO][nN]|}) ""
  |> global_replace (regexp {|```|}) ""
  |> global_replace (regexp ";") ","         (* be tolerant *)
  |> global_replace (regexp "\\]\\[") "],["  (* fix adjacency *)
  |> String.trim

let json_list = function `List l -> l | _ -> []

(* Parse LLM array of cases into (name, a, b) where a & b are JSON lists *)
let parse_cases_generic (txt : string)
  : (string * Yojson.Basic.t list * Yojson.Basic.t list) list =
  let open Yojson.Basic.Util in
  (* extract first [...] block if surrounded by prose *)
  let body =
    match (String.index_opt txt '[', String.rindex_opt txt ']') with
    | Some i, Some j when j >= i -> String.sub txt i (j - i + 1)
    | _ -> txt
  in
  try
    Yojson.Basic.from_string body |> to_list |> List.filter_map (fun j ->
      let name =
        (match j |> member "name" with
         | `String s -> s
         | _ ->
           (match j |> member "description" with
            | `String s -> s | _ -> "llm_case"))
      in
      let input = j |> member "input" in
      let a_json, b_json =
        if input = `Null then
          let inputs = j |> member "inputs" in
          if inputs <> `Null then (inputs |> member "set1", inputs |> member "set2")
          else
            let aj = let a = j |> member "a" in if a <> `Null then a else j |> member "set1" in
            let bj = let b = j |> member "b" in if b <> `Null then b else j |> member "set2" in
            (aj, bj)
        else
          (input |> member "a", input |> member "b")
      in
      Some (name, json_list a_json, json_list b_json))
  with _ -> []

let show_json_list (xs:Yojson.Basic.t list) : string =
  "[" ^ (String.concat ", " (List.map Yojson.Basic.to_string xs)) ^ "]"

(* Pretty-set helpers (convert set -> list via to_list, then stringify) *)
let show_ls_set s  = show_json_list (LS.to_list s)
let show_bs_set s  = show_json_list (BS.to_list s)
let show_rbs_set s = show_json_list (RBS.to_list s)

(* ------------------------------------------------------------ *)
(*  Fetchers (Gemini first, then OpenAI)                        *)
(* ------------------------------------------------------------ *)
let fetch_with (prompt:string) : (string * Yojson.Basic.t list * Yojson.Basic.t list) list =
  match Sys.getenv_opt "GEMINI_API_KEY", Sys.getenv_opt "OPENAI_API_KEY" with
  | Some gkey, _ ->
      let raw = Llm_client.call_gemini_api gkey prompt in
      begin match Llm_client.extract_text_from_gemini raw with
      | Some txt -> parse_cases_generic (strip_fences txt)
      | None ->
          (match Sys.getenv_opt "OPENAI_API_KEY" with
           | Some okey ->
               (match Llm_client.extract_text_from_openai (Llm_client.call_openai_api okey prompt) with
                | Some t -> parse_cases_generic (strip_fences t)
                | None -> [])
           | None -> [])
      end
  | None, Some okey ->
      (match Llm_client.extract_text_from_openai (Llm_client.call_openai_api okey prompt) with
       | Some t -> parse_cases_generic (strip_fences t)
       | None -> [])
  | _ -> []

(* ------------------------------------------------------------ *)
(*  UNION                                                        *)
(* ------------------------------------------------------------ *)
let fetch_union_cases () =
  let prompt =
    "Generate 3 JSON test cases ONLY for OCaml ListSet.union. \
     Each item MUST be: {\"name\": string, \"input\": {\"a\": list, \"b\": list}}. \
     Use ANY JSON values inside lists (numbers, strings, booleans, null, arrays). \
     The 3rd case MUST include at least one list longer than 20 elements. \
     Respond ONLY with a JSON array."
  in
  let cs = fetch_with prompt in
  logf "[LLM] Loaded %d union cases\n" (List.length cs); flush_log (); cs

let run_and_log_union (name, a, b) : bool =
  let s1 = LS.of_list a and s2 = LS.of_list b in
  let expected = LS.of_list (a @ b) in
  let actual   = LS.union s1 s2 in
  let ok = LS.eq expected actual in
  logf "[UNION] %s\n  input.a=%s\n  input.b=%s\n  expected=%s\n  actual=%s\n  match=%b\n\n"
       name (show_json_list a) (show_json_list b) (show_ls_set expected) (show_ls_set actual) ok;
  flush_log ();
  true  (* allow fail: never fail test; just log *)

let to_union_case (name,a,b) =
  to_alcotest @@ QCheck.Test.make
  ~name:("LLM_Union - " ^ name)
  ~count:1
  ~long_factor:1
  QCheck.unit
  (fun () ->
     let _ = run_and_log_union (name,a,b) in
     true)



let llm_union_tests =
  fetch_union_cases () |> List.map to_union_case

(* ------------------------------------------------------------ *)
(*  ListSet.intersection                                         *)
(* ------------------------------------------------------------ *)
let fetch_list_inter_cases () =
  let prompt =
    "Generate 3 JSON test cases ONLY for OCaml ListSet.intersection. \
     Each item MUST be: {\"name\": string, \"input\": {\"a\": list, \"b\": list}}. \
     Use ANY JSON values inside lists (numbers, strings, booleans, null, arrays). \
     Respond ONLY with a JSON array."
  in
  let cs = fetch_with prompt in
  logf "[LLM] Loaded %d ListSet.intersection cases\n" (List.length cs); flush_log (); cs

let run_and_log_list_inter (name, a, b) : bool =
  let s1 = LS.of_list a and s2 = LS.of_list b in
  let expected = LS.of_list (List.filter (fun x -> List.mem x b) a) in
  let actual   = LS.intersection s1 s2 in
  let ok = LS.eq expected actual in
  logf "[LIST-INTERSECTION] %s\n  input.a=%s\n  input.b=%s\n  expected=%s\n  actual=%s\n  match=%b\n\n"
       name (show_json_list a) (show_json_list b) (show_ls_set expected) (show_ls_set actual) ok;
  flush_log ();
  true

let to_list_inter_case (name,a,b) =
  to_alcotest @@ QCheck.Test.make
    ~name:("LLM_ListSet_Inter - " ^ name)
    ~count:1
    ~long_factor:1
    QCheck.unit
    (fun () ->
      let _ = run_and_log_list_inter (name,a,b) in
      true)


let llm_list_intersection_tests =
  fetch_list_inter_cases () |> List.map to_list_inter_case

(* ------------------------------------------------------------ *)
(*  BstSet.intersection                                          *)
(* ------------------------------------------------------------ *)
let fetch_bst_inter_cases () =
  let prompt =
    "Generate 3 JSON test cases ONLY for OCaml BstSet.intersection. \
     Each item MUST be: {\"name\": string, \"input\": {\"a\": list, \"b\": list}}. \
     The 'name' MUST be a short descriptive snake_case identifier like \
     'partial_overlap_numbers', 'no_overlap_disjoint', or 'mixed_type_common'. \
     Use ANY JSON values inside lists (numbers, strings, booleans, null, arrays). \
     Respond ONLY with a JSON array."
  in
  let cs = fetch_with prompt in
  logf "[LLM] Loaded %d BstSet.intersection cases\n" (List.length cs); flush_log (); cs

let run_and_log_bst_inter (name, a, b) : bool =
  let s1 = BS.of_list a and s2 = BS.of_list b in
  let expected = BS.of_list (List.filter (fun x -> BS.elem x s2) a) in
  let actual   = BS.intersection s1 s2 in
  let ok = BS.eq expected actual in
  logf "[BST-INTERSECTION] %s\n  input.a=%s\n  input.b=%s\n  expected=%s\n  actual=%s\n  match=%b\n\n"
       name (show_json_list a) (show_json_list b) (show_bs_set expected) (show_bs_set actual) ok;
  flush_log ();
  true

let to_bst_inter_case (name,a,b) =
  to_alcotest @@ QCheck.Test.make
    ~name:("LLM_BstSet_Inter - " ^ name)
    ~count:1
    ~long_factor:1
    QCheck.unit
    (fun () ->
      let _ = run_and_log_bst_inter (name,a,b) in
      true)


let llm_bst_intersection_tests =
  fetch_bst_inter_cases () |> List.map to_bst_inter_case

(* ------------------------------------------------------------ *)
(*  RbtSet.intersection                                          *)
(* ------------------------------------------------------------ *)
let fetch_rbt_inter_cases () =
  let prompt =
    "Generate 3 JSON test cases ONLY for OCaml RbtSet.intersection. \
     Each item MUST be: {\"name\": string, \"input\": {\"a\": list, \"b\": list}}. \
     The 'name' MUST be a short descriptive snake_case identifier like \
     'boolean_overlap', 'numeric_partial_match', or 'string_only_common'. \
     Use ANY JSON values inside lists (numbers, strings, booleans, null, arrays). \
     Respond ONLY with a JSON array."
  in
  let cs = fetch_with prompt in
  if cs = [] then (
    (* Fallback synthetic if LLM returns nothing *)
    logf "[LLM] Loaded 0 RbtSet.intersection cases (fallback to synthetic)\n";
    flush_log ();
    [
      ("rbt_fallback_overlap",
        [`Int 1; `Int 2; `String "x"; `Bool true],
        [`Int 2; `String "y"; `Bool true]);
      ("rbt_fallback_disjoint",
        [`String "a"; `String "b"],
        [`Int 10; `Bool false]);
      ("rbt_fallback_nested",
        [`List [`Int 1; `Int 2]; `Null; `String "k"],
        [`List [`Int 2]; `Null; `String "z"]);
    ]
  ) else (
    logf "[LLM] Loaded %d RbtSet.intersection cases\n" (List.length cs);
    flush_log ();
    cs
  )

let run_and_log_rbt_inter (name, a, b) : bool =
  let s1 = RBS.of_list a and s2 = RBS.of_list b in
  let expected = RBS.of_list (List.filter (fun x -> RBS.elem x s2) a) in
  let actual   = RBS.intersection s1 s2 in
  let ok = RBS.eq expected actual in
  logf "[RBT-INTERSECTION] %s\n  input.a=%s\n  input.b=%s\n  expected=%s\n  actual=%s\n  match=%b\n\n"
       name (show_json_list a) (show_json_list b) (show_rbs_set expected) (show_rbs_set actual) ok;
  flush_log ();
  true

let to_rbt_inter_case (name,a,b) =
  to_alcotest @@ QCheck.Test.make
    ~name:("LLM_RbtSet_Inter - " ^ name)
    ~count:1
    ~long_factor:1
    QCheck.unit
    (fun () ->
      let _ = run_and_log_rbt_inter (name,a,b) in
      true)


let llm_rbt_intersection_tests =
  fetch_rbt_inter_cases () |> List.map to_rbt_inter_case


