(* Minimal LLM client: ONLY provider calls + minimal JSON text extraction.
   Exposes:
     - call_gemini_api : string -> string -> string
     - extract_text_from_gemini : string -> string option
     - call_openai_api : string -> string -> string
     - extract_text_from_openai : string -> string option
     - call_nvidia_api : string -> string -> string
     - extract_text_from_nvidia : string -> string option
     - call_anthropic_api : string -> string -> string
     - extract_text_from_anthropic : string -> string option
*)

(* ---- tiny helper needed by both callers ---- *)
let read_all ic =
  let b = Buffer.create 4096 in
  (try
     while true do
       Buffer.add_string b (input_line ic);
       Buffer.add_char b '\n'
     done
   with End_of_file -> ());
  Buffer.contents b

(* ------------------------------------------------------------------ *)
(*  GEMINI)                                    *)
(* ------------------------------------------------------------------ *)

let call_gemini_api (api_key : string) (prompt : string) : string =
  let body =
    Printf.sprintf
      {|{ "contents": [ { "parts": [ { "text": %S } ] } ] }|}
      prompt
  in
  let cmd =
    Printf.sprintf
      "curl -s -X POST \
       'https://generativelanguage.googleapis.com/v1beta/models/gemini-2.5-pro:generateContent?key=%s' \
       -H 'Content-Type: application/json' -d '%s'"
      api_key body
  in
  let ic = Unix.open_process_in cmd in
  let out = read_all ic in
  ignore (Unix.close_process_in ic);
  out

let extract_text_from_gemini (raw : string) : string option =
  let open Yojson.Basic.Util in
  try
    let j = Yojson.Basic.from_string raw in
    match j |> member "candidates" with
    | `List (cand :: _) ->
        cand
        |> member "content"
        |> member "parts"
        |> to_list
        |> List.hd
        |> member "text"
        |> to_string
        |> Option.some
    | _ -> None
  with _ -> None

(* ------------------------------------------------------------------ *)
(*  OPENAI                                                            *)
(* ------------------------------------------------------------------ *)


let call_openai_api (api_key : string) (prompt : string) : string =
  let body =
    Printf.sprintf
      {|{
        "model": "gpt-4o-mini",
        "messages": [{"role":"user","content":%S}]
      }|}
      prompt
  in
  let cmd =
    Printf.sprintf
      "curl -s -X POST https://api.openai.com/v1/chat/completions \
       -H 'Content-Type: application/json' \
       -H 'Authorization: Bearer %s' -d '%s'"
      api_key body
  in
  let ic = Unix.open_process_in cmd in
  let out = read_all ic in
  ignore (Unix.close_process_in ic);
  out

let extract_text_from_openai (raw : string) : string option =
  let open Yojson.Basic.Util in
  try
    let j = Yojson.Basic.from_string raw in
    j
    |> member "choices"
    |> to_list
    |> List.hd
    |> member "message"
    |> member "content"
    |> to_string
    |> Option.some
  with _ -> None

(* ------------------------------------------------------------------ *)
(*  NVIDIA (via NVIDIA NIM / API)                                    *)
(* ------------------------------------------------------------------ *)

let call_nvidia_api (api_key : string) (prompt : string) : string =
  let body =
    Printf.sprintf
      {|{
        "model": "meta/llama-3.1-70b-instruct",
        "messages": [{"role":"user","content":%S}]
      }|}
      prompt
  in
  let cmd =
    Printf.sprintf
      "curl -s -X POST https://integrate.api.nvidia.com/v1/chat/completions \
       -H 'Content-Type: application/json' \
       -H 'Authorization: Bearer %s' \
       -d '%s'"
      api_key body
  in
  let ic = Unix.open_process_in cmd in
  let out = read_all ic in
  ignore (Unix.close_process_in ic);
  out

let extract_text_from_nvidia (raw : string) : string option =
  let open Yojson.Basic.Util in
  try
    let j = Yojson.Basic.from_string raw in
    j
    |> member "choices"
    |> to_list
    |> List.hd
    |> member "message"
    |> member "content"
    |> to_string
    |> Option.some
  with _ -> None


(* ------------------------------------------------------------------ *)
(*  Claude (Anthropic API)                                           *)
(* ------------------------------------------------------------------ *)

let call_anthropic_api (api_key : string) (prompt : string) : string =
  let body =
    Printf.sprintf
      {|{
        "model": "claude-3-5-sonnet-20241022",
        "max_tokens": 1024,
        "messages": [{"role": "user", "content": %S}]
      }|}
      prompt
  in
  let cmd =
    Printf.sprintf
      "curl -s https://api.anthropic.com/v1/messages \
       -H 'Content-Type: application/json' \
       -H 'x-api-key: %s' \
       -H 'anthropic-version: 2023-06-01' \
       -d '%s'"
      api_key body
  in
  let ic = Unix.open_process_in cmd in
  let out = read_all ic in
  ignore (Unix.close_process_in ic);
  out

let extract_text_from_anthropic (raw : string) : string option =
  let open Yojson.Basic.Util in
  try
    let j = Yojson.Basic.from_string raw in
    j
    |> member "content"
    |> to_list
    |> List.hd
    |> member "text"
    |> to_string
    |> Option.some
  with _ -> None
