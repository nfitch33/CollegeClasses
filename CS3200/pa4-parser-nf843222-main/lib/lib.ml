(* 0. Write your name and OU ID (the part before the
   "@" in your email address) below:

   NAME: Nathaniel Fitch
   ID: nf843222
 *)

open Alcotest
open Sexplib
(* https://github.com/janestreet/sexplib *)
(* https://v3.ocaml.org/p/sexplib *)

(* In utop, comment the following line out. Instead run "#use "lib/util.ml";;" *)
open Util

(** In this assignment, you'll be implementing a parser for a small
   programming language called Scheme0 Core. The syntax of this
   language follows "S-expression" form, and is given by the following
   BNF grammar:

   Unary Operators
   u ::= not           # negate a boolean

   Binary Operators
   b ::= +             # add two numbers
       | -             # subtract two numbers
       | *             # multiply two numbers
       | /             # divide two numbers
       | =             # equality on numbers
       | <             # less-than on numbers

   Values:
   v ::= true          # boolean true
       | false         # boolean false
       | n             # a number

   Expressions:
   e ::= v               # a value
       | x               # an identifier
       | (u e)           # unary op u applied to expression e
       | (b e1 e2)       # binary op b applied to e1, e2
       | (if e1 e2 e3)   # if e1 then e2 else e3
       | (let x e2 e3)   # let x = the value of e2 in e3 (in which x may appear free)

   For example, here's a valid Scheme0 Core program, in concrete syntax:

     (let x 3
         (let y 4
             (+ x y)))

   As you might expect, this program evaluates to 7.
 *)

(** Part 1: Scheme0 Core Parser

   In part 1, your job is to write a program called 'parseExp' that
   translates S-expressions into the Scheme0 Core abstract
   syntax given below. That is, we'll leave the job of actually
   parsing the concrete S-expression syntax up to the Sexp library (which has
   built-in functions for handling this sort of thing), and instead
   focus just on the translation of S-expressions into Scheme0 Core's
   abstract syntax.

   This exercise is nontrivial (meaning it may take you
   while!). Here's how I suggest you get started:

   - First, read through the Scheme0 Core abstract syntax given
     below. Make sure you understand how the abstract syntax (as
     encoded by the algebraic datatypes for Exp, Val, etc.)
     corresponds to the Scheme0 Core BNF given above.

   - Second, read the provided test cases given at the end of the
     parseExp function.

   - Third, looking at the provided template code, figure out how you
     would like to attack this problem.

   - Fourth and finally, begin programming parseExp.
 *)

(* Scheme0 Core Abstract Syntax *)

type unop =
  | UNot

type binop =
  | BAdd
  | BSub
  | BMul
  | BDiv
  | BEqu
  | BLt
  | BLe

type value =
  | VBool of bool
  | VFloat of float

let vbool b = VBool b
let vfloat x = VFloat x

type exp =
  | EVal of value
  | EIdent of string
  | EUnexp of unop * exp
  | EBinexp of binop * exp * exp
  | EIte of exp * exp * exp
  | ELet of string * exp * exp

let ebool b = EVal (VBool b)
let efloat x = EVal (VFloat x)
let eident x = EIdent x

(* END Scheme0 Core Abstract Syntax *)

module ShowUnop : Show with type t = unop = struct
  type t = unop
  let show _ = "UNot"
end

module ShowBinop : Show with type t = binop = struct
  type t = binop
  let show = function
    | BAdd  -> "BAdd"
    | BSub  -> "BSub"
    | BMul  -> "BMul"
    | BDiv  -> "BDiv"
    | BEqu  -> "BEqu"
    | BLt   -> "BLt"
    | BLe   -> "BLe"
end

module ShowValue : Show with type t = value = struct
  type t = value
  let show = function
    | VBool b -> "(VBool " ^ (if b then "true" else "false") ^ ")"
    | VFloat x -> "(VFloat " ^ string_of_float x ^ ")"
end

module ShowExp : Show with type t = exp = struct
  type t = exp
  let rec show = function
    | EVal v -> ShowValue.show v
    | EIdent x -> x
    | EUnexp (u, e) -> "(EUnexp " ^ ShowUnop.show u ^ " " ^ show e ^ ")"
    | EBinexp (b, e1, e2) ->
       "(EBinexp " ^ ShowBinop.show b ^ " " ^ show e1 ^ " " ^ show e2 ^ ")"
    | EIte (e1, e2, e3) -> "(EIte " ^ show e1 ^ " " ^ show e2 ^ " " ^ show e3 ^ ")"
    | ELet (x, e2, e3) -> "(ELet " ^ x ^ " " ^ show e2 ^ " " ^ show e3 ^ ")"
end

let value : value testable =
  let pp_value ppf e = Fmt.pf ppf "%s" (ShowValue.show e) in
  testable pp_value ( = )

let exp : exp testable =
  let pp_exp ppf e = Fmt.pf ppf "%s" (ShowExp.show e) in
  testable pp_exp ( = )

let res (x : 'a) = result x string

(* Example expressions *)
let ex0 = EIdent "x"
let ex1 = EVal  (VFloat 3.0)
let ex2 = EVal (VFloat 100.0)
let ex3 = EVal (VBool true)
let ex4 = EVal (VBool false)
let ex5 = EBinexp (BAdd, ex1, ex2)
let ex6 = EBinexp (BSub, ex1, ex2)
let ex7 = EBinexp (BMul, ex1, ex2)
let ex8 = EBinexp (BDiv, ex1, ex2)
let ex9 = EBinexp (BMul, ex8, ex8)
let ex10 = EBinexp (BMul, ex7, ex5)
let ex11 = EBinexp (BAdd, EIdent "x", EIdent "y")
let ex12 = EBinexp (BSub, EVal (VFloat 0.0), EVal (VFloat 5.0))
let ex20 = EUnexp(UNot, EVal (VBool true))
let ex30 = ELet ("x", EVal (VFloat 3.0), EIdent "x")
let ex31 = ELet ("yzw", EBinexp (BAdd, EVal (VFloat 4.0), EIdent "x"), EIdent "x")
let ex32 = ELet ("x", EBinexp (BAdd, EVal (VFloat 4.0),
                               EBinexp (BAdd, EIdent "x", EIdent "x")),
                 EBinexp (BMul, EIdent "x", EIdent "y"))
let ex33 = EIte (EVal (VBool true), EVal (VFloat 5.0), EIdent "x")
let ex34 = EIte (EVal (VBool false), EVal (VFloat 5.0), EIdent "x")
let ex35 = ELet ("x", EVal (VFloat 6.0), EIte (EVal (VBool false),
                                           EVal (VFloat 5.0), EIdent "x"))
let ex40 = ELet ("b",
                 EIte (EBinexp (BLt, EVal (VFloat 1.0), EVal (VFloat 1.0)),
                       EVal (VFloat 4.0), EVal (VFloat 5.0)),
                 EBinexp (BSub, EIdent "b", EVal (VFloat 9.0)))
let ex41 = ELet ("q", EBinexp (BEqu, EVal (VFloat 3.0), EVal (VFloat 3.0)), EIdent "q")

(** 1. (50 pts) Write a function 'parse_exp' that parses an exp from
    an s-expression. *)

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


(** helper to wrap functions in a result type *)
let wrap (error_msg : string) (f : 'a -> 'b) (x : 'a) : 'b res =
  try Ok (f x) with
  | _ -> Error error_msg

(** parse a string into a sexp *)
let sexp_of_string (s : string) : Sexp.t res =
  wrap ("failed to parse sexp: " ^ s) Sexp.of_string s

(** parse a string into an exp *)
let parse (s : string) : exp res =
  let* e = sexp_of_string s in
  parse_exp e

(** tests *)
let () = add_test "parse" @@
           fun _ ->
           (check @@ res exp) "" (Ok ex0) (parse "x");

           (* values *)
           (check @@ res exp) "" (Ok ex1) (parse "3");
           (check @@ res exp) "" (Ok ex1) (parse "   3");
           (check @@ res exp) "" (Ok ex1) (parse "3   ");
           (check @@ res exp) "" (Ok ex2) (parse "100");
           (check @@ res exp) "" (Ok ex2) (parse "   100   ");
           (check @@ res exp) "" (Ok ex3) (parse "true");
           (check @@ res exp) "" (Ok ex3) (parse "   true");
           (check @@ res exp) "" (Ok ex4) (parse "false   ");
           (check bool) "" true (is_err @@ parse ("1 2"));

           (* binexps *)
           (check @@ res exp) "" (Ok ex5) (parse "(+ 3 100)");
           (check @@ res exp) "" (Ok ex6) (parse "(- 3 100)");
           (check @@ res exp) "" (Ok ex7) (parse "(* 3 100)");
           (check @@ res exp) "" (Ok ex7) (parse "(    *   3   100   )");
           (check @@ res exp) "" (Ok ex8) (parse "(/ 3 100)");
           (check @@ res exp) "" (Ok ex9) (parse "(* (/ 3 100) (/ 3 100))");
           (check @@ res exp) "" (Ok ex10) (parse "(* (* 3 100) (+ 3 100))");
           (check @@ res exp) "" (Ok ex11) (parse "(+ x y)");
           (check @@ res exp) "" (Ok ex12) (parse "(- 0 5)");

           (* unexps *)
           (check @@ res exp) "" (Ok ex20) (parse "(not true)");
           (check bool) "" true (is_err @@ parse ("(not 1 2)"));

           (* let expressions *)
           (check @@ res exp) "" (Ok ex30) (parse "(let x 3 x)");
           (check @@ res exp) "" (Ok ex31) (parse "( let  yzw (+ 4 x) x  )");
           (check @@ res exp) "" (Ok ex32) (parse "(let x (+ 4 (+ x x)) (* x y))");
           (check bool) "" true (is_err @@ parse ("  ( let x (+ 4 (+ x x)) (*x  y  ) )"));
           (check bool) "" true (is_err @@ parse ("(let x 3 x x)"));
           (check @@ res exp) "" (Ok ex40) (parse "(let b (if (< 1 1) 4 5) (- b 9))");
           (check @@ res exp) "" (Ok ex41) (parse "(let q (= 3 3) q)");

           (* if expressions *)
           (check @@ res exp) "" (Ok ex33) (parse "(if true 5 x)");
           (check @@ res exp) "" (Ok ex34) (parse "(if false 5 x)");
           (check @@ res exp) "" (Ok ex35) (parse "(let x 6 (if false 5 x))");
           (check bool) "" true (is_err @@ parse ("(cons false 5 x)"));
           (check bool) "" true (is_err @@ parse ("(if false 5 x y)"))


(** Part 2: Scheme0 Core Interpreter

   In this part, you will implement an interpreter for the Scheme0
   Core language.

   That is, define a function `interp` that takes an initial
   environment (mapping identifiers to values) and an expression, and
   returns the result of evaluating that expression to a value. As in
   the parser assignment, you may find it helpful to break the problem
   down into smaller functions. For example, you might define
   one function for interpreting binary expressions, one for
   conditional expressions, and so on. *)

(** An environment is a function from identifiers (strings) to values. *)
type env = string -> value res

(** The initial environment contains no bindings. *)
let init_env : env = fun (x : string) -> Error (x ^ " is unbound")

(** Look up the value bound to an identifier in an environment. *)
let lookup (rho : env) (x : string) : value res = rho x

(** Update an environment with a new binding. *)
let upd (rho : env) (x : string) (new_val : value) : env =
  fun y -> if x = y then Ok new_val else rho y

let as_bool (v : value) : bool res =
  match v with
  | VBool b -> Ok b
  | _ -> Error "as_bool"

let as_float (v : value) : float res =
  match v with
  | VFloat x -> Ok x
  | _ -> Error "as_int"

(** 2. (50 pts) Write a function 'interp' that evaluates an expression
    under a given environment to produce a value. *)

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


(** End-to-end parser and interpreter. *)
let run (s : string) : value res =
  let* e = parse s in
  interp init_env e

(* These tests provide evidence that your interpreter is working properly. *)
let () = add_test "interp" @@
           fun _ ->
           (check bool) "" true (is_err @@ interp init_env ex0);
           (check @@ res value) "" (Ok (VFloat 3.0)) (interp init_env ex1);
           (check @@ res value) "" (Ok (VFloat 100.0)) (interp init_env ex2);
           (check @@ res value) "" (Ok (VBool true)) (interp init_env ex3);
           (check @@ res value) "" (Ok (VBool false)) (interp init_env ex4);
           (check @@ res value) "" (Ok (VFloat 103.0)) (interp init_env ex5);
           (check @@ res value) "" (Ok (VFloat (-97.0))) (interp init_env ex6);
           (check @@ res value) "" (Ok (VFloat 300.0)) (interp init_env ex7);
           (check @@ res value) "" (Ok (VFloat 0.03)) (interp init_env ex8);
           (check @@ res value) "" (Ok (VFloat 0.0009)) (interp init_env ex9);
           (check @@ res value) "" (Ok (VFloat 30900.0)) (interp init_env ex10);
           (check bool) "" true (is_err @@ interp init_env ex11);
           (check @@ res value) "" (Ok (VFloat (-5.0))) (interp init_env ex12);
           (check @@ res value) "" (Ok (VBool false)) (interp init_env ex20);
           (check @@ res value) "" (Ok (VFloat 3.0)) (interp init_env ex30);
           (check bool) "" true (is_err @@ interp init_env ex31);
           (check bool) "" true (is_err @@ interp init_env ex32);
           (check @@ res value) "" (Ok (VFloat 5.0)) (interp init_env ex33);
           (check bool) "" true (is_err @@ interp init_env ex34);
           (check @@ res value) "" (Ok (VFloat 6.0)) (interp init_env ex35);
           (check @@ res value) "" (Ok (VFloat (-4.0))) (interp init_env ex40);
           (check @@ res value) "" (Ok (VBool true)) (interp init_env ex41)
