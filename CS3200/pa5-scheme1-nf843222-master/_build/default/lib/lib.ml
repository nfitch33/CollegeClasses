(* 0. Write your name and OHIO ID (the part before the
   "@" in your university email address) below:
*)
let name ="Nathaniel Fitch";;
let id = "p101093645";;
let _ = Printf.printf "\n-----NAME: %s ID:%s -----\n" name id;;

open QCheck
open Alcotest
open Sexplib

open Util

(** In this assignment, you'll be extending the parser and interpreter
   from PA4 to support the Scheme1 language. The core language (and
   thus the interpreter) is extended to include anonymous functions
   and function application, and the source language is further
   extended by a handful of derived forms (handled by the
   parser). Note that although 'let' expressions were in the core
   language of Scheme0, they are derived forms in Scheme1. The new
   concrete syntax is given by the following BNF grammar:

   Unary Operators
   u ::= not           # negate a boolean
       | neg           # NEW (derived): negate a number

   Binary Operators
   b ::= +             # add two numbers
       | -             # subtract two numbers
       | *             # multiply two numbers
       | /             # divide two numbers
       | =             # equality on numbers
       | <             # less-than on numbers
       | and           # NEW (derived): boolean conjunction
       | or            # NEW (derived): boolean disjunction

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
       | (let x e2 e3)   # NEW (derived)
       | (fun x e)       # NEW (core): anonymous function with parameter x and body e
       | (e1 e2)         # NEW (core): function application (function e1 applied to e2 as an argument to e1)
 *)

(** An environment of type 'a is a function from identifiers (strings)
   to values of type 'a. *)
type 'a env = string -> 'a res

(** The initial environment contains no bindings. *)
let init_env : 'a env = fun (x : string) -> Error (x ^ " is unbound")

(** Look up the element bound to an identifier in an environment. *)
let lookup (rho : 'a env) (x : string) : 'a res = rho x

(** Update an environment with a new binding. *)
let upd (rho : 'a env) (x : string) (new_a : 'a) : 'a env =
  fun y -> if x = y then Ok new_a else rho y

(** (25 pts) Part 1: Scheme1 Parser

   In part 1, you will extend the Scheme0 Core parser from PA4 to
   support the additional syntactic forms of the Scheme1 source
   language. The updated abstract syntax is given below (the same as
   in PA4 but with a few new constructors). 
   This function is located near Line 253. *)
   
(** Scheme1 Core Abstract Syntax *)

type unop =
  | UNot
  | UNeg (* new *)

type binop =
  | BAdd
  | BSub
  | BMul
  | BDiv
  | BEqu
  | BLt
  | BLe
  | BConj (* new *)
  | BDisj (* new *)

type value =
  | VBool of bool
  | VFloat of float
  | VClos of value env * string * exp

and exp =
  | EVal of value
  | EIdent of string
  | EUnexp of unop * exp
  | EBinexp of binop * exp * exp
  | EIte of exp * exp * exp
  | ELet of string * exp * exp
  | EFun of string * exp
  | EApp of exp * exp

let vbool b = VBool b
let vfloat x = VFloat x

let ebool b = EVal (VBool b)
let efloat x = EVal (VFloat x)
let eident x = EIdent x

(** END Scheme1 Core Abstract Syntax *)

(** Part 1: Parser Implementation *)
(** Part 1: Parser Implementation *)

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
      | "neg", [e] ->                          (* new unary neg *)
          let* e' = parse_exp e in
          Ok (EUnexp (UNeg, e'))
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
      | "and", [e1; e2] ->                      (* new derived *)
          let* e1' = parse_exp e1 in
          let* e2' = parse_exp e2 in
          Ok (EBinexp (BConj, e1', e2'))
      | "or", [e1; e2] ->                       (* new derived *)
          let* e1' = parse_exp e1 in
          let* e2' = parse_exp e2 in
          Ok (EBinexp (BDisj, e1', e2'))
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
      (* anonymous functions *)
      | "fun", [Atom v; e] ->
          let* body = parse_exp e in
          Ok (EFun (v, body))
      (* function application (left-associative for multiple args) *)
      | _ ->
          (* parse operator/function as expression *)
          let* f = parse_exp (Atom op) in
          (* parse all arguments *)
          let rec fold_app f = function
            | [] -> Ok f
            | e :: rest ->
                let* arg = parse_exp e in
                fold_app (EApp (f, arg)) rest
          in
          fold_app f args
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


(** parse a string into an exp *)
let[@warning "-32"] parse (s : string) : exp res =
  let* e = sexp_of_string s in
  parse_exp e


(** Show and test modules remain unchanged *)
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
    | BConj -> "BConj"
    | BDisj -> "BDisj"
end

module rec ShowValue : Show with type t = value = struct
  type t = value
  let show = function
    | VBool b -> "(VBool " ^ (if b then "true" else "false") ^ ")"
    | VFloat x -> "(VFloat " ^ string_of_float x ^ ")"
    | VClos (_, x, e) -> "(VClos" ^ x ^ " " ^ ShowExp.show e ^ ")"
end

and ShowExp : Show with type t = exp = struct
  type t = exp
  let rec show = function
    | EVal v -> ShowValue.show v
    | EIdent x -> x
    | EUnexp (u, e) -> "(EUnexp " ^ ShowUnop.show u ^ " " ^ show e ^ ")"
    | EBinexp (b, e1, e2) ->
       "(EBinexp " ^ ShowBinop.show b ^ " " ^ show e1 ^ " " ^ show e2 ^ ")"
    | EIte (e1, e2, e3) -> "(EIte " ^ show e1 ^ " " ^ show e2 ^ " " ^ show e3 ^ ")"
    | ELet (x, e2, e3) -> "(ELet " ^ x ^ " " ^ show e2 ^ " " ^ show e3 ^ ")"
    | EFun (x, e) -> "(EFun " ^ x ^ " " ^ show e ^ ")"
    | EApp (e1, e2) -> "(EApp" ^ show e1 ^ " " ^ show e2 ^ ")"
end

(* Testing voodoo. *)
let value : value testable =
  let pp_value ppf e = Fmt.pf ppf "%s" (ShowValue.show e) in
  testable pp_value ( = )
let exp : exp testable =
  let pp_exp ppf e = Fmt.pf ppf "%s" (ShowExp.show e) in
  testable pp_exp ( = )
let res (x : 'a) = result x string
let arbitrary_unop = QCheck.make (fun _ -> UNot) ~print:ShowUnop.show
let binops = [BAdd; BSub; BMul; BDiv; BEqu; BLt; BLe; BConj; BDisj]
let binop_gen = Gen.map (List.nth binops) (Gen.int_bound 8)
let arbitrary_binop = QCheck.make binop_gen ~print:ShowBinop.show
let arbitrary_value = oneof [make (Gen.map vbool Gen.bool);
                             make (Gen.map vfloat Gen.float)]


(** (25 pts) Part 2: Free variables

    Write a function 'free' that checks if a given variable appears
    free in an expression. I.e., 'free x e' evaluates to true iff
    variable 'x' appears free in expression 'e'.

    Hint: Review the use of init_env, upd, and lookup in Pa4-parser. 
    `free` only needs to look up the variable in the environment table.
 *)

let rec free (x : string) (e : exp) : bool =
  ____todo____ (free, x, e)

let () = add_test "free" @@
           fun _ ->
           (check bool) "" true (free "x" (EIdent "x"));
           (check bool) "" true (free "x" (EUnexp (UNot, EIdent "x")));
           (check bool) "" false (free "x" (ELet ("x", EVal (VFloat 2.0), EIdent "x")));
           (check bool) "" true (free "x" (ELet ("y", EIdent "x", EVal (VFloat 0.0))));
           (check bool) "" true (free "x" (EIte (EVal (VBool false),
                                                 EBinexp (BAdd, EIdent "x",
                                                          EVal (VFloat 1.0)),
                                                 ELet ("x", EVal (VFloat 3.0),
                                                       EBinexp (BSub, EVal (VFloat 3.0),
                                                                EIdent "x")))))

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
let ex13 = EBinexp (BConj, EVal (VBool false), EVal (VBool true))
let ex14 = EBinexp (BDisj, EVal (VBool false), EVal (VBool true))
let ex15 = EBinexp (BConj, ex13, ex14)
let ex20 = EUnexp (UNot, EVal (VBool true))
let ex21 = EUnexp (UNeg, EVal (VFloat 5.0))
let ex22 = EBinexp (BAdd, EUnexp (UNeg, EVal (VFloat 2.0)),
                    EUnexp (UNeg, EVal (VFloat (-2.0))))
let ex23 = EBinexp (BAdd, EBinexp (BSub, EVal (VFloat 0.0), EVal (VFloat 2.0)),
                    EBinexp (BSub, EVal (VFloat 0.0), EVal (VFloat (-2.0))))
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
let ex50 = EFun ("x", EIdent "x")
let ex51 = EFun ("y", EBinexp(BAdd, EIdent "y" , EVal (VFloat 1.0)))
let ex52 = EFun ("x", EUnexp (UNot, EIdent "x"))
let ex53 = EFun ("x", EFun("y", EBinexp(BAdd, EIdent "x", EIdent "y")))
let ex60 = EApp (ex50, EVal (VFloat 123.0))
let ex61 = EApp (ex51, EVal (VFloat 2.0))
let ex62 = EApp (ex51, EVal (VBool false))
let ex63 = EApp (ex52, EVal (VBool false))
let ex64 = EApp (ex52, EVal (VFloat 3.0))
let ex65 = EApp (ex60, EVal (VBool true))
let ex66 = EApp (ex53, EVal (VFloat 3.0))
let ex67 = EApp (ex66, EVal (VFloat 5.0))
let ex68 = EApp (EApp (ex53, EVal (VFloat 1.0)), EVal (VBool true))
(* Ω = (λx. x x) (λx. x x) *)
let omega = EApp (EFun ("x", EApp (EIdent "x", EIdent "x")),
                  EFun("x", EApp (EIdent "x", EIdent "x")))

let rec parse_exp (s : Sexp.t) : exp res =
  ____todo____ (parse_exp, s) (* Replace with your solution. *)

let wrap (error_msg : string) (f : 'a -> 'b) (x : 'a) : 'b res =
  try Ok (f x) with
  | _ -> Error error_msg

let sexp_of_string (s : string) : Sexp.t res =
  wrap ("failed to parse sexp: " ^ s) Sexp.of_string s

let parse (s : string) : exp res =
  let* e = sexp_of_string s in
  parse_exp e

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
           (check @@ res exp) "" (Ok ex13) (parse "(and false true)");
           (check @@ res exp) "" (Ok ex14) (parse "(or false true)");
           (check @@ res exp) "" (Ok ex15) (parse "(and (and false true) (or false true))");

           (* unexps *)
           (check @@ res exp) "" (Ok ex20) (parse "(not true)");
           (check @@ res exp) "" (Ok ex21) (parse "(neg 5)");
           (check @@ res exp) "" (Ok ex22) (parse "(+ (neg 2) (neg -2))");
           (check @@ res exp) "" (Ok ex23) (parse "(+ (- 0 2) (- 0 -2))");
           (check bool) "" true (is_err @@ parse ("(not 1 2)"));

           (* let expressions *)
           (check @@ res exp) "" (Ok ex30) (parse "(let x 3 x)");
           (check @@ res exp) "" (Ok ex31) (parse "( let  yzw (+ 4 x) x  )");
           (check @@ res exp) "" (Ok ex32) (parse "(let x (+ 4 (+ x x)) (* x y))");
           (* (check bool) "" true (is_err @@ parse ("  ( let x (+ 4 (+ x x)) (\*x  y  ) )")); *)
           (check bool) "" true (is_err @@ parse ("(let x 3 x x)"));
           (check @@ res exp) "" (Ok ex40) (parse "(let b (if (< 1 1) 4 5) (- b 9))");
           (check @@ res exp) "" (Ok ex41) (parse "(let q (= 3 3) q)");

           (* if expressions *)
           (check @@ res exp) "" (Ok ex33) (parse "(if true 5 x)");
           (check @@ res exp) "" (Ok ex34) (parse "(if false 5 x)");
           (check @@ res exp) "" (Ok ex35) (parse "(let x 6 (if false 5 x))");
           (check bool) "" true (is_err @@ parse ("(cons false 5 x)"));
           (check bool) "" true (is_err @@ parse ("(if false 5 x y)"));

           (* functions *)
           (check @@ res exp) "" (Ok ex50) (parse "(fun x x)");
           (check @@ res exp) "" (Ok ex51) (parse "(fun y (+ y 1))");
           (check @@ res exp) "" (Ok ex52) (parse "(fun x (not x))");
           (check @@ res exp) "" (Ok ex53) (parse "(fun x (fun y (+ x y)))");

           (* function application*)
           (check @@ res exp) "" (Ok ex60) (parse "((fun x x) 123)");
           (check @@ res exp) "" (Ok ex61) (parse "((fun y (+ y 1)) 2)");
           (check @@ res exp) "" (Ok ex62) (parse "((fun y (+ y 1)) false)");
           (check @@ res exp) "" (Ok ex63) (parse "((fun x (not x)) false)");
           (check @@ res exp) "" (Ok ex64) (parse "((fun x (not x)) 3)");
           (check @@ res exp) "" (Ok ex65) (parse "(((fun x x) 123) true)");
           (check @@ res exp) "" (Ok ex66) (parse "((fun x (fun y (+ x y))) 3)");
           (check @@ res exp) "" (Ok ex67) (parse "(((fun x (fun y (+ x y))) 3) 5)");
           (check @@ res exp) "" (Ok ex68) (parse "(((fun x (fun y (+ x y))) 1) true)");
           (check @@ res exp) "" (Ok omega) (parse "((fun x (x x)) (fun x (x x)))")

(** (25 pts) Part 3: Scheme1 Desugarer

   Some of the new syntactic forms are technically unnecessary since
   they can be implemented in terms of existing constructs of Scheme0
   Core (in fact, some of the Scheme0 Core features aren't even
   necessary -- can you guess which ones they are?). That is, they can
   be implemented as "derived forms", or "syntactic sugar", and
   desugared to more primitive language features.

   In this part, you will implement a desugaring pass to eliminate all
   syntactic sugar, resulting in an expression containing only core
   syntax. It should be implemented as a recursive traversal through
   the expression, replacing derived forms with their translations to
   core syntax.
*)

(** Predicate asserting that an expression doesn't contain any derived forms. *)
let rec is_core : exp -> bool = function
    | EVal _ -> true
    | EIdent _ -> true
    | EUnexp _ -> false
    | EBinexp (op, e1, e2) ->
       (match op with
        | BConj | BDisj -> false
        | _ -> is_core e1 && is_core e2)
    | EIte (e1, e2, e3) -> is_core e1 && is_core e2 && is_core e3
    | ELet _ -> false
    | EFun (_, e) -> is_core e
    | EApp (e1, e2) -> is_core e1 && is_core e2

let rec desugar (e : exp) : exp =
  ____todo____ (desugar, e) (* Replace with your solution. *)

let () = add_test "desugar" @@
           fun _ ->
           (check exp) "" (EIte (EVal (VBool false), EVal (VBool true), EVal (VBool false)))
             (desugar ex13);
           (check exp) "" (EIte (EVal (VBool false), EVal (VBool true), EVal (VBool true)))
             (desugar ex14);
           (check exp) "" (EIte ((EIte (EVal (VBool false), EVal (VBool true), EVal (VBool false))), (EIte (EVal (VBool false), EVal (VBool true), EVal (VBool true))), EVal (VBool false)))
             (desugar ex15);
           (check exp) "" (EBinexp (BSub, EVal (VFloat 0.0), EVal (VFloat 5.0)))
             (desugar ex21);
           (check exp) "" ex23 (desugar ex22);
           (check exp) "" (EApp (ex50, EVal (VFloat 3.0))) (desugar ex30);
           (check exp) "" (EApp (EFun ("yzw", EIdent "x"),
                                 EBinexp (BAdd, EVal (VFloat 4.0), EIdent "x")))
             (desugar ex31);
           (check exp) "" (EIte (EVal (VBool true),
                                 EApp (ex50, EVal (VFloat 1.0)),
                                 EApp (ex50, EVal (VFloat 2.0))))
             (desugar ((EIte (EVal (VBool true),
                              ELet ("x", EVal (VFloat 1.0), EIdent "x"),
                              ELet ("x", EVal (VFloat 2.0), EIdent "x")))))
    
(** (25 pts) Part 4: Scheme1 Interpreter

   Extend your interpreter from PA4 to support functions and function
   application. Note that the interpreter only needs to implement the
   core syntax -- derived forms are eliminated by the desugarer before
   ever reaching the interpreter! The interpreter can simply produce
   an error result when it encounters any derived forms (e.g., 'let'
   expressions).

   NOTE: Be careful when interpreting EApp expressions to evaluate the
   body under the *closure environment* extended with a binding for
   the argument value (not the outer environment!).
*)

let as_bool (v : value) : bool res =
  match v with
  | VBool b -> Ok b
  | _ -> Error "as_bool"

let as_float (v : value) : float res =
  match v with
  | VFloat x -> Ok x
  | _ -> Error "as_int"

let is_boolean_binop = function
  | BConj | BDisj -> true
  | _ -> false

(** Evaluate an expression under a given environment to produce a value. *)
let rec interp (rho : value env) (e : exp) : value res =
  ____todo____ (interp, rho, e) (* Replace with your solution. *)

(** End-to-end parser, desugarer, and interpreter. *)
let run (s : string) : value res =
  let* e = parse s in
  interp init_env (desugar e)

(** These tests provide evidence that your interpreter is working properly. *)
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
           (check @@ res value) "" (Ok (VBool false)) (interp init_env ex13);
           (check @@ res value) "" (Ok (VBool true)) (interp init_env ex14);
           (check @@ res value) "" (Ok (VBool false)) (interp init_env ex15);
           (check @@ res value) "" (Ok (VBool false)) (interp init_env ex20);
           (check @@ res value) "" (Ok (VFloat (-5.0))) (interp init_env (desugar ex21));
           (check @@ res value) "" (Ok (VFloat 3.0)) (interp init_env ex30);
           (check bool) "" true (is_err @@ interp init_env ex31);
           (check bool) "" true (is_err @@ interp init_env ex32);
           (check @@ res value) "" (Ok (VFloat 5.0)) (interp init_env ex33);
           (check bool) "" true (is_err @@ interp init_env ex34);
           (check @@ res value) "" (Ok (VFloat 6.0)) (interp init_env ex35);
           (check @@ res value) "" (Ok (VFloat (-4.0))) (interp init_env ex40);
           (check @@ res value) "" (Ok (VBool true)) (interp init_env ex41);
           (check @@ res value) "" (Ok (VFloat 123.0)) (interp init_env (desugar ex60));
           (check @@ res value) "" (Ok (VFloat 3.0)) (interp init_env (desugar ex61));
           (check bool) "" true (is_err @@ interp init_env ex62);
           (check @@ res value) "" (Ok (VBool true)) (interp init_env (desugar ex63));
           (check bool) "" true (is_err @@ interp init_env ex64);
           (check bool) "" true (is_err @@ interp init_env ex65);
           (check @@ res value) "" (Ok (VFloat 8.0)) (interp init_env (desugar ex67));
           (check bool) "" true (is_err @@ interp init_env ex68);

           (* Implementing multiplication as repeated addition via the
              Y combinator:
              Y = λf. (λx. f (λy. x x y)) (λx. f (λy. x x y)) *)
           (check @@ res value) "" (Ok (VFloat 30.0))
             (let fix = EFun ("f", EApp (EFun ("x", EApp (EIdent "f", EFun ("y", EApp (EApp (EIdent "x", EIdent "x"), EIdent "y")))), EFun ("x", EApp (EIdent "f", EFun ("y", EApp (EApp (EIdent "x", EIdent "x"), EIdent "y")))))) in
              let mult_g = EFun ("f", EFun ("m", EFun ("n", EIte (EBinexp (BEqu, EIdent "n", EVal (VFloat 0.0)), EVal (VFloat 0.0), EBinexp (BAdd, EIdent "m", EApp (EApp (EIdent "f", EIdent "m" ), EBinexp (BSub, EIdent "n", EVal (VFloat 1.0)))))))) in
              let nat_mult = EApp(fix, mult_g) in
              interp init_env (EApp (EApp (nat_mult, EVal (VFloat 5.0)), EVal (VFloat 6.0))))

let () = ()
