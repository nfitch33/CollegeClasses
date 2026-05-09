open QCheck_alcotest

let string_of_list (show : 'a -> string) (l : 'a list) : string =
  "[" ^ String.concat ", " (List.map show l) ^ "]"

module type Show = sig
  type t
  val show : t -> string (* render to string *)
end

let is_ok = function
  | Ok _ -> true
  | _ -> false

let is_err = function
  | Error _ -> true
  | _ -> false

type 'a res = ('a, string) result

let (let*) = Result.bind
let (let+) x f = Result.map f x

let rec seq (l : ('a res) list) : ('a list) res =
  match l with
  | [] -> Ok []
  | x :: xs ->
     let* x' = x in
     let* xs' = seq xs in
     Ok (x' :: xs')

let mapM (f : 'a -> 'b res) (l : 'a list) : ('b list) res =
  seq @@ List.map f l

(** Testing voodoo. Feel free to ignore. *)

let todo (type t) (x : t) : 'a =
  let module M = struct exception Todo of t end in
  raise @@ M.Todo x

let ____todo____ = todo

let tests = ref []
let qcheck_tests = ref []

let add_test nm t = tests := !tests @ [Alcotest.test_case nm `Quick t]
let add_qcheck_ t = tests := !tests @ [to_alcotest t]

let add_qcheck t = qcheck_tests := !qcheck_tests @ [to_alcotest t]
