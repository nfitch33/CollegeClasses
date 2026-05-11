(* 0. Write your name and OU ID (the part before the
   "@" in your email address) below:

   NAME: Nathaniel Fitch
   ID: p101093645
   EMAIL: nf843222@ohio.edu
 *)

open QCheck
open Alcotest
open Sexplib

open Util

(** Typed Scheme1

  In this assignment, you'll be extending Scheme1 Core to Typed
  Scheme1 Core. First, you'll extend the parser to support the
  extended syntax given below (which includes types and 'rec'
  expressions). Then, in part 2, you'll implement a typechecker!

  Note that our trick for encoding recursion no longer works once we
  add a type system (try to recreate the 'omega' example from PA5 in
  the new typed language -- it won't be typeable!), so to maintain
  support for recursive computations, we must add a new syntactic form
  to the core language for recursive bindings. An expression of the
  form '(rec x t e)' should be understood as "let x stand for
  recursive occurrences of e in e, where e (and thus x as well) has
  type t".

  Types
  t ::= bool
      | num
      | (-> t1 t2)
   
  Unary Operators
  u ::= not           # negate a boolean
      | neg           # negate a number (derived)

  Binary Operators
  b ::= +             # add two numbers
      | -             # subtract two numbers
      | *             # multiply two numbers
      | /             # divide two numbers
      | =             # equality on numbers
      | <             # less-than on numbers
      | and           # boolean conjunction (derived)
      | or            # boolean disjunction (derived)

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
      | (let x t e2 e3) # let expression (derived)
      | (fun x t e)     # anonymous function with parameter x of type t and body e
      | (e1 e2)         # function application (e1 applied to argument e2)
      | (rec x t e)     # NEW: recursive definition. let x stand for recursive occurrences in e.
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

(** (25 pts) Part 1: Typed Scheme1 Parser

   Extend the Scheme0 Core parser to parse types (now included in type
   annotations on 'let', 'fun', and 'rec' expressions) as well as
   'rec' expressions.
*)

(** Scheme0 Core Abstract Syntax *)

(* ty is type; TArrow is function *)
type ty = 
  | TBool
  | TFloat
  | TArrow of ty * ty

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
  | VClos of exp env * string * exp

and exp =
  | EVal of value
  | EIdent of string
  | EUnexp of unop * exp
  | EBinexp of binop * exp * exp
  | EIte of exp * exp * exp
  | ELet of string * ty * exp * exp
  | EFun of string * ty * exp
  | EApp of exp * exp
  | ERec of string * ty * exp

let vbool b = VBool b
let vfloat x = VFloat x

let ebool b = EVal (VBool b)
let efloat x = EVal (VFloat x)
let eident x = EIdent x

(** END Scheme0 Core Abstract Syntax *)

module ShowTy : Show with type t = ty = struct
  type t = ty
  let rec show = function
    | TBool -> "TBool"
    | TFloat -> "TFloat"
    | TArrow (s, t) -> "(-> " ^ show s ^ " " ^ show t ^ ")"
end

module ShowUnop : Show with type t = unop = struct
  type t = unop
  let show = function
    | UNot -> "UNot"
    | UNeg -> "UNeg"
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
    | ELet (x, t, e2, e3) ->
       "(EIte " ^ x ^ " " ^ ShowTy.show t ^ " " ^ show e2 ^ " " ^ show e3 ^ ")"
    | EFun (x, t, e) -> "(EFun " ^ x ^ " " ^ ShowTy.show t ^ " " ^ show e ^ ")"
    | EApp (e1, e2) -> "(EApp" ^ show e1 ^ " " ^ show e2 ^ ")"
    | ERec (x, t, e) -> "(ERec " ^ x ^ " " ^ ShowTy.show t ^ " " ^ show e ^ ")"
end

(* Testing voodoo. *)
let ty : ty testable =
  let pp_ty ppf t = Fmt.pf ppf "%s" (ShowTy.show t) in
  testable pp_ty ( = )
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

let rec free (x : string) (e : exp) : bool =
  match e with
  | EVal _ -> false
  | EIdent y -> x = y
  | EUnexp (_, e1) -> free x e1
  | EBinexp (_, e1, e2) -> free x e1 || free x e2
  | EIte (e1, e2, e3) -> free x e1 || free x e2 || free x e3
  | ELet (y, _, e1, e2) -> free x e1 || (x <> y) && free x e2
  | EFun (y, _, e) -> x <> y && free x e
  | EApp (e1, e2) -> free x e1 || free x e2
  | ERec (y, _, e) -> x <> y && free x e

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
let ex30 = ELet ("x", TFloat, EVal (VFloat 3.0), EIdent "x")
let ex31 = ELet ("yzw", TFloat, EBinexp (BAdd, EVal (VFloat 4.0), EIdent "x"), EIdent "x")
let ex32 = ELet ("x", TFloat, EBinexp (BAdd, EVal (VFloat 4.0),
                                       EBinexp (BAdd, EIdent "x", EIdent "x")),
                 EBinexp (BMul, EIdent "x", EIdent "y"))
let ex33 = EIte (EVal (VBool true), EVal (VFloat 5.0), EIdent "x")
let ex34 = EIte (EVal (VBool false), EVal (VFloat 5.0), EIdent "x")
let ex35 = ELet ("x", TFloat, EVal (VFloat 6.0), EIte (EVal (VBool false),
                                                       EVal (VFloat 5.0), EIdent "x"))
let ex40 = ELet ("b", TBool,
                 EIte (EBinexp (BLt, EVal (VFloat 1.0), EVal (VFloat 1.0)),
                       EVal (VFloat 4.0), EVal (VFloat 5.0)),
                 EBinexp (BSub, EIdent "b", EVal (VFloat 9.0)))
let ex41 = ELet ("q", TBool, EBinexp (BEqu, EVal (VFloat 3.0), EVal (VFloat 3.0)), EIdent "q")
let ex50 = EFun ("x", TFloat, EIdent "x")
let ex51 = EFun ("y", TFloat, EBinexp(BAdd, EIdent "y" , EVal (VFloat 1.0)))
let ex52 = EFun ("x", TBool, EUnexp (UNot, EIdent "x"))
let ex53 = EFun ("x", TFloat, EFun("y", TFloat, EBinexp(BAdd, EIdent "x", EIdent "y")))
let ex60 = EApp (ex50, EVal (VFloat 123.0))
let ex61 = EApp (ex51, EVal (VFloat 2.0))
let ex62 = EApp (ex51, EVal (VBool false))
let ex63 = EApp (ex52, EVal (VBool false))
let ex64 = EApp (ex52, EVal (VFloat 3.0))
let ex65 = EApp (ex60, EVal (VBool true))
let ex66 = EApp (ex53, EVal (VFloat 3.0))
let ex67 = EApp (ex66, EVal (VFloat 5.0))
let ex68 = EApp (EApp (ex53, EVal (VFloat 1.0)), EVal (VBool true))
(* Ω = (λx. x x) (λx. x x) NO LONGER TYPE-ABLE, but should still parse *)
let omega = EApp (EFun ("x", TArrow (TFloat, TFloat), EApp (EIdent "x", EIdent "x")),
                  EFun ("x", TArrow (TFloat, TFloat), EApp (EIdent "x", EIdent "x")))

(* Divergence is still possible. *)
let ex70 = ERec ("x", TFloat, EIdent "x")

(* Multiplication from repeated addition is still possible using 'rec'. *)
let nat_mult =
  ERec ("mult", TArrow (TFloat, TArrow (TFloat, TFloat)),
        EFun ("m", TFloat,
              EFun ("n", TFloat,
                    EIte (EBinexp (BEqu, EIdent "n", EVal (VFloat 0.0)),
                          EVal (VFloat 0.0),
                          EBinexp (BAdd, EIdent "m",
                                   EApp (EApp (EIdent "mult", EIdent"m"),
                                         EBinexp(BSub, EIdent "n", EVal (VFloat 1.0))))))))

let rec parse_ty (s : Sexp.t) : ty res =
  match s with
  | Sexp.Atom "bool" -> Ok TBool
  | Sexp.Atom "float" -> Ok TFloat
  | Sexp.List [Sexp.Atom "->"; t1; t2] ->
      let* ty1 = parse_ty t1 in
      let* ty2 = parse_ty t2 in
      Ok (TArrow (ty1, ty2))
  | _ -> Error ("invalid type: " ^ Sexp.to_string_hum s)


let rec parse_exp (s : Sexp.t) : exp res =
  match s with
  | Sexp.Atom "true" -> Ok (ebool true)
  | Sexp.Atom "false" -> Ok (ebool false)
  | Sexp.Atom n -> (
      try Ok (efloat (float_of_string n))
      with _ -> Ok (eident n))
  | Sexp.List (Sexp.Atom "not" :: e :: []) ->
      let* e = parse_exp e in
      Ok (EUnexp (UNot, e))
  | Sexp.List (Sexp.Atom "neg" :: e :: []) ->
      let* e = parse_exp e in
      Ok (EUnexp (UNeg, e))
  | Sexp.List (Sexp.Atom "+" :: e1 :: e2 :: []) ->
      let* e1 = parse_exp e1 in
      let* e2 = parse_exp e2 in
      Ok (EBinexp (BAdd, e1, e2))
  | Sexp.List (Sexp.Atom "-" :: e1 :: e2 :: []) ->
      let* e1 = parse_exp e1 in
      let* e2 = parse_exp e2 in
      Ok (EBinexp (BSub, e1, e2))
  | Sexp.List (Sexp.Atom "*" :: e1 :: e2 :: []) ->
      let* e1 = parse_exp e1 in
      let* e2 = parse_exp e2 in
      Ok (EBinexp (BMul, e1, e2))
  | Sexp.List (Sexp.Atom "/" :: e1 :: e2 :: []) ->
      let* e1 = parse_exp e1 in
      let* e2 = parse_exp e2 in
      Ok (EBinexp (BDiv, e1, e2))
  | Sexp.List (Sexp.Atom "=" :: e1 :: e2 :: []) ->
      let* e1 = parse_exp e1 in
      let* e2 = parse_exp e2 in
      Ok (EBinexp (BEqu, e1, e2))
  | Sexp.List (Sexp.Atom "<" :: e1 :: e2 :: []) ->
      let* e1 = parse_exp e1 in
      let* e2 = parse_exp e2 in
      Ok (EBinexp (BLt, e1, e2))
  | Sexp.List (Sexp.Atom "and" :: e1 :: e2 :: []) ->
      let* e1 = parse_exp e1 in
      let* e2 = parse_exp e2 in
      Ok (EBinexp (BConj, e1, e2))
  | Sexp.List (Sexp.Atom "or" :: e1 :: e2 :: []) ->
      let* e1 = parse_exp e1 in
      let* e2 = parse_exp e2 in
      Ok (EBinexp (BDisj, e1, e2))
  | Sexp.List (Sexp.Atom "if" :: e1 :: e2 :: e3 :: []) ->
      let* e1 = parse_exp e1 in
      let* e2 = parse_exp e2 in
      let* e3 = parse_exp e3 in
      Ok (EIte (e1, e2, e3))
  | Sexp.List (Sexp.Atom "let" :: Sexp.Atom x :: ty_s :: e1 :: e2 :: []) ->
      let* t = parse_ty ty_s in
      let* e1 = parse_exp e1 in
      let* e2 = parse_exp e2 in
      Ok (ELet (x, t, e1, e2))
  | Sexp.List (Sexp.Atom "fun" :: Sexp.Atom x :: ty_s :: e :: []) ->
      let* t = parse_ty ty_s in
      let* e = parse_exp e in
      Ok (EFun (x, t, e))
  | Sexp.List (Sexp.Atom "rec" :: Sexp.Atom x :: ty_s :: e :: []) ->
      let* t = parse_ty ty_s in
      let* e = parse_exp e in
      Ok (ERec (x, t, e))
  | Sexp.List (f :: arg :: []) ->
      let* f = parse_exp f in
      let* arg = parse_exp arg in
      Ok (EApp (f, arg))
  | _ -> Error ("invalid expression: " ^ Sexp.to_string_hum s)

  
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
           (check @@ res exp) "" (Ok ex30) (parse "(let x float 3 x)");
           (check @@ res exp) "" (Ok ex31) (parse "( let  yzw float (+ 4 x) x  )");
           (check @@ res exp) "" (Ok ex32) (parse "(let x float (+ 4 (+ x x)) (* x y))");
           (check bool) "" true (is_err @@ parse ("(let x float 3 x x)"));
           (check @@ res exp) "" (Ok ex40) (parse "(let b bool (if (< 1 1) 4 5) (- b 9))");
           (check @@ res exp) "" (Ok ex41) (parse "(let q bool (= 3 3) q)");

           (* if expressions *)
           (check @@ res exp) "" (Ok ex33) (parse "(if true 5 x)");
           (check @@ res exp) "" (Ok ex34) (parse "(if false 5 x)");
           (check @@ res exp) "" (Ok ex35) (parse "(let x float 6 (if false 5 x))");
           (check bool) "" true (is_err @@ parse ("(cons false 5 x)"));
           (check bool) "" true (is_err @@ parse ("(if false 5 x y)"));

           (* functions *)
           (check @@ res exp) "" (Ok ex50) (parse "(fun x float x)");
           (check @@ res exp) "" (Ok ex51) (parse "(fun y float (+ y 1))");
           (check @@ res exp) "" (Ok ex52) (parse "(fun x bool (not x))");
           (check @@ res exp) "" (Ok ex53) (parse "(fun x float (fun y float (+ x y)))");

           (* function application*)
           (check @@ res exp) "" (Ok ex60) (parse "((fun x float x) 123)");
           (check @@ res exp) "" (Ok ex61) (parse "((fun y float (+ y 1)) 2)");
           (check @@ res exp) "" (Ok ex62) (parse "((fun y float (+ y 1)) false)");
           (check @@ res exp) "" (Ok ex63) (parse "((fun x bool (not x)) false)");
           (check @@ res exp) "" (Ok ex64) (parse "((fun x bool (not x)) 3)");
           (check @@ res exp) "" (Ok ex65) (parse "(((fun x float x) 123) true)");
           (check @@ res exp) "" (Ok ex66)
             (parse "((fun x float (fun y float (+ x y))) 3)");
           (check @@ res exp) "" (Ok ex67)
             (parse "(((fun x float (fun y float (+ x y))) 3) 5)");
           (check @@ res exp) "" (Ok ex68)
             (parse "(((fun x float (fun y float (+ x y))) 1) true)");
           (check @@ res exp) "" (Ok omega)
             (parse "((fun x (-> float float) (x x)) (fun x (-> float float) (x x)))");

           (* recursive definitions *)
           (check @@ res exp) "" (Ok ex70) (parse "(rec x float x)");
           (check @@ res exp) "" (Ok nat_mult)
             (parse "(rec mult (-> float (-> float float)) \
                     (fun m float (fun n float (if (= n 0) 0 (+ m ((mult m) (- n 1)))))))")

(** (25 pts) Part 2: Typed Scheme1 Desugarer

   Now, extend the desugarer to account for the new syntax. There
   isn't much to do here since the syntax extensions are fairly
   trivial.
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
    | EFun (_, _, e) -> is_core e
    | EApp (e1, e2) -> is_core e1 && is_core e2
    | ERec (_, _, e) -> is_core e

let rec desugar (e : exp) : exp =
  match e with
  | EVal _ | EIdent _ -> e
  | EUnexp (UNeg, e1) ->
      let e1' = desugar e1 in
      EBinexp (BSub, EVal (VFloat 0.0), e1')
  | EUnexp (UNot, e1) ->
      let e1' = desugar e1 in
      EUnexp (UNot, e1')
  | EBinexp (BConj, e1, e2) ->
      let e1' = desugar e1 in
      let e2' = desugar e2 in
      EIte (e1', e2', EVal (VBool false))
  | EBinexp (BDisj, e1, e2) ->
      let e1' = desugar e1 in
      let e2' = desugar e2 in
      EIte (e1', EVal (VBool true), e2')
  | EBinexp (op, e1, e2) ->
      EBinexp (op, desugar e1, desugar e2)
  | EIte (e1, e2, e3) ->
      EIte (desugar e1, desugar e2, desugar e3)
  | ELet (x, t, e1, e2) ->
      let e1' = desugar e1 in
      let e2' = desugar e2 in
      EApp (EFun (x, t, e2'), e1')
  | EFun (x, t, e1) ->
      EFun (x, t, desugar e1)
  | EApp (e1, e2) ->
      EApp (desugar e1, desugar e2)
  | ERec (x, t, e1) ->
      ERec (x, t, desugar e1)


let () = add_test "desugar" @@
           fun _ ->
           (check exp) "" (EIte (EVal (VBool false),
                                 EVal (VBool true), EVal (VBool false)))
             (desugar ex13);
           (check exp) "" (EIte (EVal (VBool false),
                                 EVal (VBool true), EVal (VBool true)))
             (desugar ex14);
           (check exp) "" (EIte ((EIte (EVal (VBool false),
                                        EVal (VBool true), EVal (VBool false))),
                                 (EIte (EVal (VBool false), EVal (VBool true),
                                        EVal (VBool true))), EVal (VBool false)))
             (desugar ex15);
           (check exp) "" (EBinexp (BSub, EVal (VFloat 0.0), EVal (VFloat 5.0)))
             (desugar ex21);
           (check exp) "" ex23 (desugar ex22);
           (check exp) "" (EApp (ex50, EVal (VFloat 3.0))) (desugar ex30);
           (check exp) "" (EApp (EFun ("yzw", TFloat, EIdent "x"),
                                 EBinexp (BAdd, EVal (VFloat 4.0), EIdent "x")))
             (desugar ex31);
           (check exp) "" (EIte (EVal (VBool true),
                                 EApp (ex50, EVal (VFloat 1.0)),
                                 EApp (ex50, EVal (VFloat 2.0))))
             (desugar ((EIte (EVal (VBool true),
                              ELet ("x", TFloat, EVal (VFloat 1.0), EIdent "x"),
                              ELet ("x", TFloat, EVal (VFloat 2.0), EIdent "x")))))

(** (25 pts) Part 3: Scheme1 Core Typechecker

   Now, it's time to implement a typechecker for Scheme1 Core! Write a
   function 'tycheck' that computes the type of a Scheme1 Core
   expression under a given typing context (or producing an error if
   the expression is not typeable).

   Refer to the typing relation document at
      ../scheme1_core_typing.pdf
   for the typing rules. Recall that the Greek letter Γ (capital
   "Gamma") stands for the typing context, and the notation "Γ, x:T"
   stands for Γ updated with a new binding, mapping variable x to type T.

   NOTE: VClos values don't have a typing rule because they aren't
   expected to appear in source programs. This means your typechecker
   should produce an Error if it sees a VClos!
*)

let rec assert_ty (gamma : ty env) (expected_ty : ty) (e : exp) : ty res =
  let* t = tycheck gamma e in
  if t = expected_ty then Ok t
  else Error ("assert_ty: expected " ^ ShowTy.show expected_ty
              ^ ", got " ^ ShowTy.show t)

and tycheck (gamma : ty env) (e : exp) : ty res =
  match e with
  | EVal (VBool _) -> Ok TBool
  | EVal (VFloat _) -> Ok TFloat
  | EVal (VClos _) ->
      Error "VClos should not appear in surface programs"

  | EIdent x ->
      lookup gamma x

  | EUnexp (UNot, e1) ->
      let* t1 = tycheck gamma e1 in
      if t1 = TBool then Ok TBool
      else Error "not expects a bool"

  | EUnexp (UNeg, _) ->
      (* neg is desugared away; UNeg is never seen in core *)
      Error "UNeg should not appear after desugaring"

  | EBinexp (op, e1, e2) ->
      let* t1 = tycheck gamma e1 in
      let* t2 = tycheck gamma e2 in
      (match op, t1, t2 with
       | (BAdd | BSub | BMul | BDiv), TFloat, TFloat -> Ok TFloat
       | (BEqu | BLt), TFloat, TFloat -> Ok TBool
       | BLe, TFloat, TFloat -> Ok TBool
       | _ -> Error "binary operator applied to wrong types")

  | EIte (e1, e2, e3) ->
      let* t1 = tycheck gamma e1 in
      if t1 <> TBool then Error "if condition must be bool" else
      let* t2 = tycheck gamma e2 in
      let* t3 = tycheck gamma e3 in
      if t2 = t3 then Ok t2
      else Error "branches of if have different types"

  | EFun (x, t_param, body) ->
      let gamma' = upd gamma x t_param in
      let* t_body = tycheck gamma' body in
      Ok (TArrow (t_param, t_body))

  | EApp (e1, e2) ->
      let* t_fun = tycheck gamma e1 in
      let* t_arg = tycheck gamma e2 in
      (match t_fun with
       | TArrow (t_in, t_out) ->
           if t_arg = t_in then Ok t_out
           else Error "function argument type mismatch"
       | _ -> Error "attempted to apply a non-function")

  | ERec (x, t, e1) ->
      (* Γ, x:t ⊢ e1 : t must hold *)
      let gamma' = upd gamma x t in
      let* t1 = tycheck gamma' e1 in
      if t1 = t then Ok t
      else Error "recursive definition has wrong type"

  | ELet _ ->
      (* should never appear in core; desugared into EApp(EFun...) *)
      Error "ELet should not appear after desugaring"

  
let () = add_test "tycheck" @@
           fun _ ->
           (* unbound variable *)
           (check bool) "" true (is_err @@ tycheck init_env (desugar ex0));
           (check bool) "" true (is_err @@ tycheck init_env (desugar ex11));
           (check bool) "" true (is_err @@ tycheck init_env (desugar ex31));
           (check bool) "" true (is_err @@ tycheck init_env (desugar ex32));
           (check bool) "" true (is_err @@ tycheck init_env (desugar ex33));
           (check bool) "" true (is_err @@ tycheck init_env (desugar ex34));

           (check @@ res ty) "" (Ok TFloat) (tycheck init_env (desugar ex1));
           (check @@ res ty) "" (Ok TFloat) (tycheck init_env (desugar ex2));
           (check @@ res ty) "" (Ok TBool) (tycheck init_env (desugar ex3));
           (check @@ res ty) "" (Ok TBool) (tycheck init_env (desugar ex4));
           (check @@ res ty) "" (Ok TFloat) (tycheck init_env (desugar ex5));
           (check @@ res ty) "" (Ok TFloat) (tycheck init_env (desugar ex6));
           (check @@ res ty) "" (Ok TFloat) (tycheck init_env (desugar ex7));
           (check @@ res ty) "" (Ok TFloat) (tycheck init_env (desugar ex8));
           (check @@ res ty) "" (Ok TFloat) (tycheck init_env (desugar ex9));
           (check @@ res ty) "" (Ok TFloat) (tycheck init_env (desugar ex10));
           (check @@ res ty) "" (Ok TFloat) (tycheck init_env (desugar ex12));
           (check @@ res ty) "" (Ok TBool) (tycheck init_env (desugar ex13));
           (check @@ res ty) "" (Ok TBool) (tycheck init_env (desugar ex14));
           (check @@ res ty) "" (Ok TBool) (tycheck init_env (desugar ex15));
           (check @@ res ty) "" (Ok TBool) (tycheck init_env (desugar ex20));
           (check @@ res ty) "" (Ok TFloat) (tycheck init_env (desugar ex21));
           (check @@ res ty) "" (Ok TFloat) (tycheck init_env (desugar ex22));
           (check @@ res ty) "" (Ok TFloat) (tycheck init_env (desugar ex23));
           (check @@ res ty) "" (Ok TFloat) (tycheck init_env (desugar ex30));
           (check @@ res ty) "" (Ok TFloat) (tycheck init_env (desugar ex35));

           (* wrong type annotation *)
           (check bool) "" true (is_err @@ tycheck init_env (desugar ex40));

           (check @@ res ty) "" (Ok (TArrow (TFloat, TFloat)))
             (tycheck init_env (desugar ex50));
           (check @@ res ty) "" (Ok (TArrow (TFloat, TFloat)))
             (tycheck init_env (desugar ex51));
           (check @@ res ty) "" (Ok (TArrow (TBool, TBool)))
             (tycheck init_env (desugar ex52));
           (check @@ res ty) "" (Ok (TArrow (TFloat, TArrow (TFloat, TFloat))))
             (tycheck init_env (desugar ex53));
           (check @@ res ty) "" (Ok (TArrow (TBool, TFloat)))
             (tycheck init_env (EFun ("b", TBool,
                                      EIte (EIdent "b",
                                            EVal (VFloat 1.0), EVal (VFloat 0.0)))));
           (check @@ res ty) "" (Ok TFloat) (tycheck init_env (desugar ex60));
           (check @@ res ty) "" (Ok TFloat) (tycheck init_env (desugar ex61));
           (check @@ res ty) "" (Ok TBool) (tycheck init_env (desugar ex63));

           (* expects float argument *)
           (check bool) "" true (is_err @@ tycheck init_env (desugar ex62));

           (* expects bool argument *)
           (check bool) "" true (is_err @@ tycheck init_env (desugar ex64));

           (* can't apply number *)
           (check bool) "" true (is_err @@ tycheck init_env (desugar ex65));

           (check @@ res ty) "" (Ok (TArrow (TFloat, TFloat)))
             (tycheck init_env (desugar ex66));
           (check @@ res ty) "" (Ok TFloat) (tycheck init_env (desugar ex67));
           (check @@ res ty) "" (Ok TFloat) (tycheck init_env (desugar ex70));
           (check @@ res ty) "" (Ok (TArrow (TFloat, TArrow (TFloat, TFloat))))
             (tycheck init_env (desugar nat_mult));

           (* expects float second argument *)
           (check bool) "" true (is_err @@ tycheck init_env (desugar ex68));

           (* Omega no longer typeable *)
           (check bool) "" true (is_err @@ tycheck init_env (desugar omega))

(** Part 4 (25 pts) Scheme1 Core interpreter

   Lastly, you must extend the interpreter to support recursive
   definitions. You can consult the bigstep semantics document at
     ../scheme1_core_bigstep.pdf
   to see how it should be done.

   NOTE: To support ERec, we generalize environments to hold
   *expressions* rather than values. You'll have to make some
   modifications to the old interpreter to account for this.
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
let rec interp (rho : exp env) (e : exp) : value res =
  match e with
  | EVal v -> Ok v

  | EIdent x ->
      let* e' = lookup rho x in
      interp rho e'

  | EUnexp (UNot, e1) ->
      let* v1 = interp rho e1 in
      let* b = as_bool v1 in
      Ok (VBool (not b))

  | EUnexp (UNeg, _) ->
      (* neg should be desugared away *)
      Error "UNeg should not appear in core"

  | EBinexp (op, e1, e2) ->
      let* v1 = interp rho e1 in
      let* v2 = interp rho e2 in
      (match op with
       | BAdd ->
           let* x1 = as_float v1 in
           let* x2 = as_float v2 in
           Ok (VFloat (x1 +. x2))
       | BSub ->
           let* x1 = as_float v1 in
           let* x2 = as_float v2 in
           Ok (VFloat (x1 -. x2))
       | BMul ->
           let* x1 = as_float v1 in
           let* x2 = as_float v2 in
           Ok (VFloat (x1 *. x2))
       | BDiv ->
           let* x1 = as_float v1 in
           let* x2 = as_float v2 in
           Ok (VFloat (x1 /. x2))
       | BEqu ->
           let* x1 = as_float v1 in
           let* x2 = as_float v2 in
           Ok (VBool (x1 = x2))
       | BLt ->
           let* x1 = as_float v1 in
           let* x2 = as_float v2 in
           Ok (VBool (x1 < x2))
       | BLe ->
           let* x1 = as_float v1 in
           let* x2 = as_float v2 in
           Ok (VBool (x1 <= x2))
       | BConj | BDisj ->
           (* should never appear: desugared away *)
           Error "boolean binop should not appear in core")

  | EIte (e1, e2, e3) ->
      let* v1 = interp rho e1 in
      let* b = as_bool v1 in
      if b then interp rho e2 else interp rho e3

  | EFun (x, _, body) ->
      Ok (VClos (rho, x, body))

  | EApp (e1, e2) ->
      let* v1 = interp rho e1 in
      let* v2 = interp rho e2 in
      (match v1 with
       | VClos (rho_clos, x, body) ->
           let rho' = upd rho_clos x (EVal v2) in
           interp rho' body
       | _ ->
           Error "application of non-function")

  | ERec (x, _, e1) ->
      (* ρ' = ρ[x → rec x t e1] *)
      let rho' = upd rho x e in
      interp rho' e1

  | ELet _ ->
      Error "ELet should not appear after desugaring"

  
(** End-to-end parser, desugarer, typechecker, and interpreter. *)
let run (s : string) : value res =
  let* e = parse s in
  let e_core = desugar e in
  let* _ = tycheck init_env e_core in
  interp init_env e_core

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
           (check @@ res value) "" (Ok (VBool false)) (interp init_env (desugar ex13));
           (check @@ res value) "" (Ok (VBool true)) (interp init_env (desugar ex14));
           (check @@ res value) "" (Ok (VBool false)) (interp init_env (desugar ex15));
           (check @@ res value) "" (Ok (VBool false)) (interp init_env (desugar ex20));
           (check @@ res value) "" (Ok (VFloat (-5.0))) (interp init_env (desugar ex21));
           (check @@ res value) "" (Ok (VFloat 3.0)) (interp init_env (desugar ex30));
           (check bool) "" true (is_err @@ interp init_env ex31);
           (check bool) "" true (is_err @@ interp init_env ex32);
           (check @@ res value) "" (Ok (VFloat 5.0)) (interp init_env ex33);
           (check bool) "" true (is_err @@ interp init_env ex34);
           (check @@ res value) "" (Ok (VFloat 6.0)) (interp init_env (desugar ex35));
           (check @@ res value) "" (Ok (VFloat (-4.0))) (interp init_env (desugar ex40));
           (check @@ res value) "" (Ok (VBool true)) (interp init_env (desugar ex41));
           (check @@ res value) "" (Ok (VFloat 123.0)) (interp init_env (desugar ex60));
           (check @@ res value) "" (Ok (VFloat 3.0)) (interp init_env (desugar ex61));
           (check bool) "" true (is_err @@ interp init_env ex62);
           (check @@ res value) "" (Ok (VBool true)) (interp init_env (desugar ex63));
           (check bool) "" true (is_err @@ interp init_env ex64);
           (check bool) "" true (is_err @@ interp init_env ex65);
           (check @@ res value) "" (Ok (VFloat 8.0)) (interp init_env (desugar ex67));
           (check bool) "" true (is_err @@ interp init_env ex68);

           (check @@ res value) "" (Ok (VFloat 30.0))
             (interp init_env (EApp (EApp (nat_mult, EVal (VFloat 5.0)), EVal (VFloat 6.0))))

let () = ()
