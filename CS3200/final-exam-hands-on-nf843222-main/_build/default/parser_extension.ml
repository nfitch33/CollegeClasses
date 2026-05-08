open Printf

open Sexplib

let _use (_ : 'a) = ()


let passed_count = ref 0
let failed_count = ref 0

let _ =
  printf "\n+++++++++++++++++++++++++++++ Parser & Interpreter Extension Problem +++++++++++++++++++++++++++++ \n"
;;

(* ===============================================================
   Problem: Parser & Interpreter Extension
   ============================================================== *)

let _ =
  printf "\n+++++++++++++++++++++++++++++ Parser & Interpreter Extension Problem +++++++++++++++++++++++++++++ \n"
;;

(**********************************************************************
Explanation of This Problem
---------------------------

This problem extends a small Scheme-like language by adding three new
binary operators:

    and     boolean AND     (short-circuiting)
    or      boolean OR      (short-circuiting)
    <=      numeric less-than-or-equal

Only two parts of the system need to be updated:

  a. The PARSER (parse_exp)
     - Converts S-expressions into AST nodes.
     - Must detect incorrect forms, such as:
           (and true)
           (and true false true)
           (<= 5)
           (or)

  b. The INTERPRETER (interp)
     - Evaluates AST expressions to values.
     - Must support:
           • short-circuit evaluation rules
           • type checking
           • boolean results for the ≤ operator

Example behaviors:

    (and false X)  ==> false        ; second argument ignored
    (or true X)    ==> true         ; second argument ignored
    (<= 4 5)       ==> true
    (<= 10 2)      ==> false

The task is to complete both parse_exp and interp.  
All necessary helper functions are already included.

***********************************************************************)




type 'a res = ('a, string) result
let _use_res (_ : int res option) = ()


(* ============================ AST TYPES ============================= *)

type binop =
  | BAdd | BSub | BMul | BDiv | BEqu | BLt
  | BAnd          (* and *)
  | BOr           (* or *)
  | BLeq          (* <= *)
;;

type value =
  | VBool of bool
  | VFloat of float

type exp =
  | EVal of value
  | EIdent of string
  | EBinexp of binop * exp * exp
;;

let _force_use_EIdent () =
  let _ = EIdent "placeholder" in
  ()


(* ============================ Part a: PARSER ============================= *)


let rec parse_exp sexp =
  (*replace this inside body with your implementation*)     (* 3 *)
  let _self = parse_exp in (* prevents unused-rec warning *)
  _use _self;
  _use sexp;
  Error "Not implemented"
  (*//*)
;;

(* or *)
(* and true .  and true false true  . <= 5*)




(* ============================ Helpers for interpreter ============================= *)

let as_bool = function
  | VBool b -> Ok b
  | _ -> Error "Expected bool"

let as_float = function
  | VFloat f -> Ok f
  | _ -> Error "Expected float"


(* ============================ Part b: INTERPRETER ============================= *)

(* interp : exp -> value res *)
let rec interp e =
  (*replace this inside body with your implementation*)   (* 4 *)
  let _self = interp in (* prevents unused-rec warning *)
  _use _self;
  _use e;
  Error "Not implemented"
  (*//**)
;;


(* ============================ TESTING ============================= *)

let pretty name f =
  let result =
    try f (); true
    with _ -> false
  in
  if result then
    (Printf.printf "%s : PASS\n" name;
     incr passed_count)
  else
    (Printf.printf "%s : FAIL\n" name;
     incr failed_count)

module Tests = struct
  let suite =
    [

      ("parse (and true false)", fun () ->
        let sexp = Sexp.of_string "(and true false)" in
        match parse_exp sexp with
        | Ok (EBinexp (BAnd, _, _)) -> ()
        | _ -> failwith "Expected parsed BAnd"
      );

      ("parse (or false true)", fun () ->
        let sexp = Sexp.of_string "(or false true)" in
        match parse_exp sexp with
        | Ok (EBinexp (BOr, _, _)) -> ()
        | _ -> failwith "Expected parsed BOr"
      );

      ("parse (<= 3 10)", fun () ->
        let sexp = Sexp.of_string "(<= 3 10)" in
        match parse_exp sexp with
        | Ok (EBinexp (BLeq, _, _)) -> ()
        | _ -> failwith "Expected parsed BLeq"
      );

      ("parse error: (and true)", fun () ->
        match parse_exp (Sexp.of_string "(and true)") with
        | Error _ -> ()
        | _ -> failwith "Expected arity error"
      );

      ("parse error: (and true false true)", fun () ->
        match parse_exp (Sexp.of_string "(and true false true)") with
        | Error _ -> ()
        | _ -> failwith "Expected arity error"
      );

      ("interp (and false X) short-circuits", fun () ->
        match interp (EBinexp (BAnd, EVal (VBool false), EVal (VFloat 10.0))) with
        | Ok (VBool false) -> ()
        | _ -> failwith "Expected false"
      );

      ("interp (and true false)", fun () ->
        match interp (EBinexp (BAnd, EVal (VBool true), EVal (VBool false))) with
        | Ok (VBool false) -> ()
        | _ -> failwith "Expected false"
      );

      ("interp (or true X) short-circuits", fun () ->
        match interp (EBinexp (BOr, EVal (VBool true), EVal (VFloat 999.0))) with
        | Ok (VBool true) -> ()
        | _ -> failwith "Expected true"
      );

      ("interp (<= 4 5)", fun () ->
        match interp (EBinexp (BLeq, EVal (VFloat 4.0), EVal (VFloat 5.0))) with
        | Ok (VBool true) -> ()
        | _ -> failwith "Expected true"
      );

      ("interp (<= 10 2)", fun () ->
        match interp (EBinexp (BLeq, EVal (VFloat 10.0), EVal (VFloat 2.0))) with
        | Ok (VBool false) -> ()
        | _ -> failwith "Expected false"
      );

      ("interp error: (and 3 true)", fun () ->
        match interp (EBinexp (BAnd, EVal (VFloat 3.0), EVal (VBool true))) with
        | Error _ -> ()
        | _ -> failwith "Expected type error"
      );

    ]
end



let _ =
  List.iter (fun (name, fn) -> pretty name fn) Tests.suite;

  Printf.printf "\n================ SUMMARY ================\n";
  Printf.printf "PASSED: %d\n" !passed_count;
  Printf.printf "FAILED: %d\n" !failed_count;
  Printf.printf "=========================================\n"


(* avoid unused warnings *)

let _ = 
  _use parse_exp;
  _use interp;
  _use as_bool;
  _use as_float;
  _use BAnd;
  _use BOr;
  _use BLeq;
  _use BDiv;
  _use BEqu;
  _use BLt;
  _use BAdd;
  _use BSub;
  _use BMul;

(* force type res usage *)
  _use_res None;

(* force EIdent usage *)
_force_use_EIdent ();