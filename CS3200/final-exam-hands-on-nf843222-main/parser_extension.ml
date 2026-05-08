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


let rec parse_exp (s : Sexp.t) : exp res =
  let open Result in
  match s with
  | Atom a -> (
      try
        Ok (EVal (VFloat (float_of_string a)))  (* parse number *)
      with _ ->
        match String.lowercase_ascii a with
        | "true" -> Ok (EVal (VBool true))      (* parse boolean true *)
        | "false" -> Ok (EVal (VBool false))    (* parse boolean false *)
        | var -> Ok (EIdent var)                (* parse identifier *)
    )
  | List [] -> Error "empty expression"
  | List (Atom op :: args) -> (
      match op, args with
      (* unary operations *)
      | "not", [e] ->
          let* e' = parse_exp e in
          Ok (EUnexp (UNot, e'))
      (* binary operations *)
      | "+", [e1; e2] ->
          let* e1' = parse_exp e1 in
          let* e2' = parse_exp e2 in
          Ok (EBinexp (BAdd, e1', e2'))
      | "-", [e1; e2] ->
          let* e1' = parse_exp e1 in
          let* e2' = parse_exp e2 in
          Ok (EBinexp (BSub, e1', e2'))
      | "*", [e1; e2] ->
          let* e1' = parse_exp e1 in
          let* e2' = parse_exp e2 in
          Ok (EBinexp (BMul, e1', e2'))
      | "/", [e1; e2] ->
          let* e1' = parse_exp e1 in
          let* e2' = parse_exp e2 in
          Ok (EBinexp (BDiv, e1', e2'))
      | "<", [e1; e2] ->
          let* e1' = parse_exp e1 in
          let* e2' = parse_exp e2 in
          Ok (EBinexp (BLt, e1', e2'))
      | "=", [e1; e2] ->
          let* e1' = parse_exp e1 in
          let* e2' = parse_exp e2 in
          Ok (EBinexp (BEqu, e1', e2'))
      (* let expressions *)
      | "let", [Atom v; e1; e2] ->
          let* e1' = parse_exp e1 in
          let* e2' = parse_exp e2 in
          Ok (ELet (v, e1', e2'))
      (* if expressions *)
      | "if", [cond; e_then; e_else] ->
          let* c = parse_exp cond in
          let* t = parse_exp e_then in
          let* f = parse_exp e_else in
          Ok (EIte (c, t, f))
      | _ -> Error ("unknown expression or wrong arity: " ^ op)
    )
  | List _ -> Error "malformed expression"
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
let rec interp (rho : env) (e : exp) : value res =
  let open Result in
  match e with
  | EVal v -> Ok v
  | EIdent x -> lookup rho x
  | EUnexp (u, e1) ->
      let* v1 = interp rho e1 in
      (match u, v1 with
       | UNot, VBool b -> Ok (VBool (not b))
       | UNot, _ -> Error "expected boolean for 'not'")
  | EBinexp (b, e1, e2) ->
      let* v1 = interp rho e1 in
      let* v2 = interp rho e2 in
      (match b, v1, v2 with
       | BAdd, VFloat x, VFloat y -> Ok (VFloat (x +. y))
       | BSub, VFloat x, VFloat y -> Ok (VFloat (x -. y))
       | BMul, VFloat x, VFloat y -> Ok (VFloat (x *. y))
       | BDiv, VFloat x, VFloat y -> Ok (VFloat (x /. y))
       | BEqu, VFloat x, VFloat y -> Ok (VBool (x = y))
       | BLt, VFloat x, VFloat y -> Ok (VBool (x < y))
       | BLe, VFloat x, VFloat y -> Ok (VBool (x <= y))
       | _, _, _ -> Error "type error in binary operation")
  | EIte (cond, e_then, e_else) ->
      let* v_cond = interp rho cond in
      let* b = as_bool v_cond in
      if b then interp rho e_then else interp rho e_else
  | ELet (x, e1, e2) ->
      let* v1 = interp rho e1 in
      let rho' = upd rho x v1 in
      interp rho' e2
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