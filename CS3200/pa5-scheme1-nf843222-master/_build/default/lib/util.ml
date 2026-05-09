open QCheck
open QCheck_alcotest

let string_of_list (show : 'a -> string) (l : 'a list) : string =
  "[" ^ String.concat ", " (List.map show l) ^ "]"

(* Module type for types that can be rendered to string. *)
module type Show = sig
  type t
  val show : t -> string (* render to string *)
end

(** A type that can be randomly generated and converted to string. *)
module type Type = sig
  include Show
  val gen : t arbitrary  (* qcheck generator for random values *)
end

(** Ordered types. *)
module type OType = sig
  include Type
  val le : t -> t -> bool (* less-than-or-equal-to, a ≤ b *)
end


let is_ok = function
  | Ok _ -> true
  | _ -> false

let is_err = function
  | Error _ -> true
  | _ -> false

(* Shorthand type for results with string errors. *)
type 'a res = ('a, string) result

(* Monadic syntax. *)
let (let*) = Result.bind
let (let+) x f = Result.map f x

(* ['a res] -> ['a] res *)
let rec seq (l : ('a res) list) : ('a list) res =
  match l with
  | [] -> Ok []
  | x :: xs ->
     let* x' = x in
     let* xs' = seq xs in
     Ok (x' :: xs')

(* Map a monadic action over a list. *)
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
