open Alcotest
open QCheck
open Sexplib

open Pa5__Lib
open Pa5__Util

let read_file filename =
  let ch = open_in filename in
  let s = really_input_string ch (in_channel_length ch) in
  close_in ch;
  s

(* Names of failing programs (without extension) *)
let fail_names =
  Sys.readdir "../../../tests/fail"
  |> Array.to_list
  |> List.filter (fun s -> Filename.extension s = ".scm")
  |> List.map Filename.remove_extension

(* Names of passing programs (without extension) *)
let pass_names : string list =
  Sys.readdir "../../../tests/pass"
  |> Array.to_list
  |> List.filter (fun s -> Filename.extension s = ".scm")
  |> List.map Filename.remove_extension

(* Source of failing programs *)
let fail_programs =
  List.map (fun nm -> read_file @@ "../../../tests/fail/" ^ nm ^ ".scm") fail_names

(* Source of passing programs *)
let pass_programs =
  List.map (fun nm -> read_file @@ "../../../tests/pass/" ^ nm ^ ".scm") pass_names

let parse_value (s : Sexp.t) : value res =
  match s with
  | Atom x ->
      (match x with
       | "true" -> Ok (VBool true)
       | "false" -> Ok (VBool false)
       | _ ->
           (match float_of_string_opt x with
            | Some n -> Ok (VFloat n)
            | _ -> Error "parse_value"))
  | _ -> Error "parse_value"

let pass_expected_values : value list =
  Result.get_ok
  @@ mapM
       (fun nm ->
         let* s =
           sexp_of_string
           @@ read_file @@ "../../../tests/pass/" ^ nm ^ ".expected"
         in
         parse_value s)
       pass_names

(** Run test programs that are expected to produce either parser or
    interpreter errors. *)
let run_fail =
  Alcotest.test_case "run_fail" `Quick @@ fun _ ->
  List.iter
    (fun s ->
      (check Alcotest.bool) ("should fail: " ^ s) true (is_err @@ run s))
    fail_programs

(** Run test programs that are expected to successfully produce a
    value, and compare against their expected values. *)
let run_pass =
  Alcotest.test_case "run_pass" `Quick @@ fun _ ->
  List.iter
    (fun (s, v) ->
      (check @@ res value) "" (Ok v) (run s))
    (List.combine pass_programs pass_expected_values)

module Int : OType = struct
  type t = int
  let le = (<=)
  let gen = small_int
  let show = string_of_int
end

(** Run the rest of the tests. *)
let () =
  Alcotest.run "PA5"
    [ ("test", !tests)
    ; ("qcheck", !qcheck_tests @ Llm_test.llm_pa5_tests)
    ; ("prog", [run_fail; run_pass]) ]

