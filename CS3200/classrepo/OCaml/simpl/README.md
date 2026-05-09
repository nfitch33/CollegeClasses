## SimpPL: A Simple Programming Language.

This is based on the simple calculator example from: https://github.com/cs3110/textbook.

Example expressions:
```ocaml
2
1+2
2+1
3*2+5*6
if 3= 5+2 then 3 else 2
let x= 22 in x
let x= 22 in x+3

if 1+2 <= 3*4 then let x = 22 in x else 0
let x =22 in if 1+2 <= 3*4 then x+2 else 0
let x = 3 in if x <= 4 then true else false
```

Additional expressions not supported by the origianl code from the textbook:
```ocaml
let x =22 in if 3-2 <= 3*4 then x-2 else 0
let x =22 in if 3/2 <= 3*4 then x-2 else 15/5
```

Simple Calculator Syntax in BNF (Backus-Naur Form):
```
e ::= x
    | i
    | b
    | e1 bop e2
    | if e1 then e2 else e3
    | let x = e1 in e2
(* e is expression *)

bop ::= + | * | <=
(* bop: binary operator *)
(* Potential expansion:
bop ::= + | - | * | / | <= | < | > | >=
*)

x ::= <identifiers>

i ::= <integers>
(* i: integer *)

b ::= true | false
(* b: boolean *)
```

Well-typed example:
```
1 + 1   (2)
3 * 2   (6)
3 >= 2  (true) 
```

Ill-typed example:
```
true + false
3 > true
```

Section 9.2.4. Example: SimPL BNF
https://cs3110.github.io/textbook/chapters/interp/parsing.html

https://cs3110.github.io/textbook/chapters/interp/substitution.html
Operational semantics can be divided into two styles:  small step vs. big step semantics.
* small-step: `-->` transform the program in one single execution step
* big-step: `==>` reduces an expression all the way to a single value
* in-between: `-->*`

Commands that work in this folder:
```
dune build
```
or
```
make test
```


Use this command to run it in utop:
```
dune utop src
```

![](https://imgur.com/AG4YbjJ.png)
![Screenshot 2024-10-30 at 9 59 19 PM](https://github.com/user-attachments/assets/cbc21cbb-4ce9-4ee8-9389-618423541ea4)

More examples:

```
─( 17:54:47 )─< command 7 >──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # parse "if 1+2 <= 3*4 then let x = 22 in x else 0";;
- : expr =
If (Binop (Leq, Binop (Add, Int 1, Int 2), Binop (Mult, Int 3, Int 4)),
 Let ("x", Int 22, Var "x"), Int 0)
─( 17:54:47 )─< command 8 >──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # interp_small "if 1+2 <= 3*4 then let x = 22 in x else 0";;
- : expr = Int 22
─( 18:07:44 )─< command 9 >──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # interp_big "if 1+2 <= 3*4 then let x = 22 in x else 0";;
- : expr = Int 22
─( 18:08:24 )─< command 10 >─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # interp_big "if 1+22 <= 3*4 then let x = 22 in x else 0";;
- : expr = Int 0
─( 18:08:32 )─< command 11 >─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # interp_small "if 1+22 <= 3*4 then let x = 22 in x else 0";;
- : expr = Int 0
─( 18:08:53 )─< command 12 >─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # 
```

```
utop # parse "if 1+2 <= 3*4 then let x = 22 in x else 0";;
- : expr =
If (
    Binop (
        Leq,
            Binop (Add, Int 1, Int 2),
            Binop (Mult, Int 3, Int 4)),
    Let ("x", Int 22, Var "x"),
    Int 0)
```

```
If (
    Binop (
        Leq,
            Int 3,
            Binop (Mult, Int 3, Int 4)),
    Let ("x", Int 22, Var "x"),
    Int 0)
```


```
If (
    Binop (
        Leq,
            Int 3,
            Int 12),
    Let ("x", Int 22, Var "x"),
    Int 0)
```

```
If (
    Bool true),
    Let ("x", Int 22, Var "x"),
    Int 0)
```


### Complete `utop` Examples
Direct invokation of `parse` `step` `is_value` `eval_big` `eval_small` `interp_big` `interp_small` `typeof` and `typecheck`
```ocaml
@drchangliu ➜ /workspaces/cs3200/OCaml/simpl (main) $ opam switch
#  switch       compiler                    description
→  cs3200.4.13  ocaml-base-compiler.4.13.0  cs3200.4.13
   cs3200.4.14  ocaml-base-compiler.4.14.0  cs3200.4.14
   cs3200.5.0   ocaml-base-compiler.5.0.0   cs3200.5.0
   cs3200.5.2   ocaml-base-compiler.5.2.0   cs3200.5.2
   default      ocaml-system.4.08.1         default

[WARNING] The environment is not in sync with the current switch.
          You should run: eval $(opam env)
@drchangliu ➜ /workspaces/cs3200/OCaml/simpl (main) $ eval $(opam env)
@drchangliu ➜ /workspaces/cs3200/OCaml/simpl (main) $ opam switch
#  switch       compiler                    description
→  cs3200.4.13  ocaml-base-compiler.4.13.0  cs3200.4.13
   cs3200.4.14  ocaml-base-compiler.4.14.0  cs3200.4.14
   cs3200.5.0   ocaml-base-compiler.5.0.0   cs3200.5.0
   cs3200.5.2   ocaml-base-compiler.5.2.0   cs3200.5.2
   default      ocaml-system.4.08.1         default
@drchangliu ➜ /workspaces/cs3200/OCaml/simpl (main) $ dune utop src
───────────────────────────────┬─────────────────────────────────────────────────────────────┬───────────────────────────────
                               │ Welcome to utop version 2.14.0 (using OCaml version 5.0.0)! │                               
                               └─────────────────────────────────────────────────────────────┘                               

Type #utop_help for help about using utop.

─( 21:38:11 )─< command 1 >───────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # open Interp;;
─( 21:39:33 )─< command 5 >───────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # open Ast;;
─( 21:40:24 )─< command 8 >───────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # open Main;;
─( 21:40:32 )─< command 9 >───────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # parse "if 1+2 <= 3*4 then let x = 22 in x else 0";;
- : expr =
If (Binop (Leq, Binop (Add, Int 1, Int 2), Binop (Mult, Int 3, Int 4)),
 Let ("x", Int 22, Var "x"), Int 0)
─( 21:40:41 )─< command 10 >──────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # parse "if 1+2 <= 3*4 then let x = 22 in x else 0" |> step;;
- : expr =
If (Binop (Leq, Int 3, Binop (Mult, Int 3, Int 4)), Let ("x", Int 22, Var "x"),
 Int 0)
─( 21:40:43 )─< command 11 >──────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # parse "if 1+2 <= 3*4 then let x = 22 in x else 0" |> step |> step;;
- : expr = If (Binop (Leq, Int 3, Int 12), Let ("x", Int 22, Var "x"), Int 0)
─( 21:41:09 )─< command 12 >──────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # parse "if 1+2 <= 3*4 then let x = 22 in x else 0" |> step |> step |> eval_small;;
- : expr = Int 22
─( 21:41:22 )─< command 13 >──────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # parse "if 1+2 <= 3*4 then let x = 22 in x else 0" |> eval_big;;
- : expr = Int 22
─( 21:41:34 )─< command 14 >──────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # parse "if 1+2 <= 3*4 then let x = 22 in x else 0" |> is_value;;
- : bool = false
─( 21:44:41 )─< command 15 >──────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # parse "if 1+2 <= 3*4 then let x = 22 in x else 0" |> eval_big |> is_value;;
- : bool = true
─( 21:44:49 )─< command 16 >──────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # parse "let x =22 in if 1+2 <= 3*4 then x+2 else 0" |> eval_big;;
- : expr = Int 24
─( 21:45:04 )─< command 17 >──────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # parse "let x =22 in if 1+2 <= 3*4 then x+2 else 0" ;;
- : expr =
Let ("x", Int 22,
 If (Binop (Leq, Binop (Add, Int 1, Int 2), Binop (Mult, Int 3, Int 4)),
  Binop (Add, Var "x", Int 2), Int 0))
─( 21:46:46 )─< command 18 >──────────────────────────────────────────────────────────
utop # parse "if 1+2 <= 3*4 then let x = 22 in x else 0" |> typeof Context.empty ;;
- : typ = TInt
─( 02:57:48 )─< command 19 >───────────────────────── ────────────────────────────────────────────────────────{ counter: 0 }─
utop # typeof Context.empty (parse "let x = 3 in if x <= 4 then true else false");;
- : typ = TBool
─( 02:57:49 )─< command 20 >───────────────────────── ────────────────────────────────────────────────────────{ counter: 0 }─
utop # parse "if 1+2 <= 3*4 then let x = 22 in x else 0" |> typecheck;;
- : unit = ()
─( 02:57:55 )─< command 21 >───────────────────────── ────────────────────────────────────────────────────────{ counter: 0 }─
utop # parse "if 1+2 <= 3*4 then let x = 22 in x else false" |> typecheck;;
Exception: Failure "Branches of if must have same type".
```


## How to file Pull Requests
* Fork the repo on github. (Or if you already forked that, sync the repo.)
* Check your changes into your forked repo
* Go to the Pull Request page of the original repo, file a pull request.
