# Ch.9 Interpreter (key concepts)

* Steps in compiler/interpreter construction
  * Lexer (input: a stream of chars -> a stream of tokens)
  * Parser (a stream of tokens -> an AST)
  * Transformation of the AST (small step vs. big step)
  * Reaching a single value (in the case of a calculator) or a suitable form to be directly translated to binary code.
* Desugaring: The following three lines are equivalent:
```
let x = e1 in e2;;
((fun x -> e2) e1);;
(e3 e1);;   (* e3 is (fun x -> e2). This is function application, function e3 applied to e1 as an argument to e3. *)
```
* Big vs. small evaluation
  * For all expressions `e` and values `v`, it holds that `e -->* v` if and only if `e ==> v`.
  * If an expression takes many small steps and eventually reaches a value, e.g., `e --> e1 --> .... --> en --> v`, then it ought to be the case that `e ==> v`. So the big step relation is a faithful abstraction of the small step relation: it just forgets about all the intermediate steps.
  * Single-step implementation example: ch9.3.2.
* Substitution vs. environment models
  * In substitution model, a notation: `e'{e/x}` means "the expression `e'` with `e` substituted for `x` ".
    * Example: `let x = v1 in e2 --> e2{v1/x}` 
  * In env models, substitutions are lazily recorded in a dictionary (which is called the env).
    * Notation: `<env, e> --> e'`, or `<env, e> ==> v`, where `env` denotes the environment, and `<env, e>` is called a **machine configuration**. 

* The `menhir` package in OCaml is a popular parser generator tool that is used to create parsers for programming languages and other structured text. Menhir is similar in purpose to tools like `Yacc` or `Bison`, commonly used in other programming languages.

### Question:
* How to prove the recursive function `eval_small` in ch9.3.3 "multistep relatio" alway converges, i.e. the recursion will eventually reach a base case and terminate?

### Code segments from the textbook
```ocaml
(** [is_value e] is whether [e] is a value. *)
let is_value : expr -> bool = function
  | Int _ | Bool _ -> true
  | Var _ | Let _ | Binop _ | If _ -> false

(** [subst e v x] is [e{v/x}]. *)
let subst _ _ _ =
  failwith "See next section"

(** [step] is the [-->] relation, that is, a single step of
    evaluation. *)
let rec step : expr -> expr = function
  | Int _ | Bool _ -> failwith "Does not step"
  | Var _ -> failwith "Unbound variable"
  | Binop (bop, e1, e2) when is_value e1 && is_value e2 ->
    step_bop bop e1 e2
  | Binop (bop, e1, e2) when is_value e1 ->
    Binop (bop, e1, step e2)
  | Binop (bop, e1, e2) -> Binop (bop, step e1, e2)
  | Let (x, e1, e2) when is_value e1 -> subst e2 e1 x
  | Let (x, e1, e2) -> Let (x, step e1, e2)
  | If (Bool true, e2, _) -> e2
  | If (Bool false, _, e3) -> e3
  | If (Int _, _, _) -> failwith "Guard of if must have type bool"
  | If (e1, e2, e3) -> If (step e1, e2, e3)

(** [step_bop bop v1 v2] implements the primitive operation
    [v1 bop v2].  Requires: [v1] and [v2] are both values. *)
and step_bop bop e1 e2 = match bop, e1, e2 with
  | Add, Int a, Int b -> Int (a + b)
  | Mult, Int a, Int b -> Int (a * b)
  | Leq, Int a, Int b -> Bool (a <= b)
  | _ -> failwith "Operator and operand type mismatch"
```

```ocaml
let rec eval_small (e : expr) : expr =
  if is_value e then e
  else e |> step |> eval_small
```

```ocaml
(** [eval_big e] is the [e ==> v] relation. *)
let rec eval_big (e : expr) : expr = match e with
  | Int _ | Bool _ -> e
  | Var _ -> failwith "Unbound variable"
  | Binop (bop, e1, e2) -> eval_bop bop e1 e2
  | Let (x, e1, e2) -> subst e2 (eval_big e1) x |> eval_big
  | If (e1, e2, e3) -> eval_if e1 e2 e3

(** [eval_bop bop e1 e2] is the [e] such that [e1 bop e2 ==> e]. *)
and eval_bop bop e1 e2 = match bop, eval_big e1, eval_big e2 with
  | Add, Int a, Int b -> Int (a + b)
  | Mult, Int a, Int b -> Int (a * b)
  | Leq, Int a, Int b -> Bool (a <= b)
  | _ -> failwith "Operator and operand type mismatch"

(** [eval_if e1 e2 e3] is the [e] such that [if e1 then e2 else e3 ==> e]. *)
and eval_if e1 e2 e3 = match eval_big e1 with
  | Bool true -> eval_big e2
  | Bool false -> eval_big e3
  | _ -> failwith "Guard of if must have type bool"
```



### Try the following feature-incomplete but compilable code segement in [OCamlPro](http://try.ocamlpro.com)

```ocaml
(** The type of binary operators. *)
type bop = 
  | Add
  | Mult
  | Leq

(** The type of the abstract syntax tree (AST). *)
type expr =
  | Var of string
  | Int of int
  | Bool of bool  
  | Binop of bop * expr * expr
  | Let of string * expr * expr
  | If of expr * expr * expr


(** [is_value e] is whether [e] is a value. *)
let is_value : expr -> bool = function
  | Int _ | Bool _ -> true
  | Var _ | Let _ | Binop _ | If _ -> false

(** [subst e v x] is [e{v/x}]. *)
let subst _ _ _ =
  failwith "See next section"

(** [step] is the [-->] relation, that is, a single step of
    evaluation. *)
let rec step : expr -> expr = function
  | Int _ | Bool _ -> failwith "Does not step"
  | Var _ -> failwith "Unbound variable"
  | Binop (bop, e1, e2) when is_value e1 && is_value e2 ->
      step_bop bop e1 e2
  | Binop (bop, e1, e2) when is_value e1 ->
      Binop (bop, e1, step e2)
  | Binop (bop, e1, e2) -> Binop (bop, step e1, e2)
  | Let (x, e1, e2) when is_value e1 -> subst e2 e1 x
  | Let (x, e1, e2) -> Let (x, step e1, e2)
  | If (Bool true, e2, _) -> e2
  | If (Bool false, _, e3) -> e3
  | If (Int _, _, _) -> failwith "Guard of if must have type bool"
  | If (e1, e2, e3) -> If (step e1, e2, e3)

(** [step_bop bop v1 v2] implements the primitive operation
    [v1 bop v2].  Requires: [v1] and [v2] are both values. *)
and step_bop bop e1 e2 = match bop, e1, e2 with
  | Add, Int a, Int b -> Int (a + b)
  | Mult, Int a, Int b -> Int (a * b)
  | Leq, Int a, Int b -> Bool (a <= b)
  | _ -> failwith "Operator and operand type mismatch"
           
;;
let e = (If (
    Binop (
      Leq,
      Int 3,
      Int 12),
    Let ("x", Int 22, Var "x"),
    Int 0))
;;

let e1 = step e 
;;

let e2 = step e1;;

is_value e2;;

let e3 = step e2;;

e |> step |> step ;; 

e |> step |> step |> is_value;; 

e |> step |> step |> step |> is_value;; 
```
