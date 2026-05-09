[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/bXZi21-1)
# cs3200-pa4-parser

Update lib/lib.ml so that the two todo placeholders are implemented with actual OCaml code.

### Sexplib (Symbolic Expression Library)
Install necessary packages using `opam`. For example 

```
 opam install sexplib ppx_deriving
```

To learn more about sexp (S Expressions, or Symbolic Expression), visit:
* https://dev.realworldocaml.org/data-serialization.html
* https://en.wikipedia.org/wiki/S-expression
* https://ocaml.org/p/sexplib/v0.13.0/doc/Sexplib/Sexp/index.html
* https://ocaml.org/u/bd9ea4958618f07dc668d43ce1eecd7c/base/v0.11.1/doc/Base/Sexp/index.html


### Module Result

<summary>Module `Result` is used for more straightforward exception handling. </summary>

<details>
More info about `Module Result`:
* https://v2.ocaml.org/api/Result.html
* https://ocaml.org/p/base/v0.16.3/doc/Base/Result/index.html

`Result` is in a sense an `Option` with an error message. In `Optoin`, it's only `None` when there is no valid value.

Bind and Map in Module Result in OCaml are two functions that can be used to manipulate Result values.

Bind takes a Result value and a function as arguments, and returns a new Result value. The function is applied to the value of the Result value, if it is Ok. If the Result value is Error, the new Result value is Error.

Map  takes a Result value and a function as arguments, and returns a new Result value. The function is applied to the value of the Result value, if it is Ok. The new Result value is Ok if the function returns a value, and Error if the function returns None.

The main difference between Bind and Map in Module Result in OCaml is that Bind can propagate errors, while Map cannot. In other words, if the function that is passed to Bind raises an exception, the Result value will be Error. If the function that is passed to Map raises an exception, the Result value will also be Error, but the exception will not be propagated.
</details>

### Building the project
Use `dune test` to compile and test the program. The initial output should look like this:

```
changliu@TABLET8:~/root/cs3200/pa4-parser-drchangliu$ dune test
File "lib/dune", line 3, characters 44-51:
3 |  (libraries alcotest qcheck qcheck-alcotest sexplib))
                                                ^^^^^^^
Error: Library "sexplib" not found.
-> required by library "pa4" in _build/default/lib
-> required by executable pa4 in test/dune:2
-> required by _build/default/test/pa4.exe
-> required by alias test/runtest in test/dune:2
```

```
changliu@TABLET8:~/root/cs3200/pa4-parser-drchangliu$ opam install sexplib
The following actions will be performed:
  ∗ install parsexp v0.15.0 [required by sexplib]
  ∗ install sexplib v0.15.1
===== ∗ 2 =====
Do you want to continue? [Y/n] y

<><> Processing actions <><><><><><><><><><><><><><><><><><><><><><><><><><><><>
⬇ retrieved sexplib.v0.15.1  (https://opam.ocaml.org/cache)
⬇ retrieved parsexp.v0.15.0  (https://opam.ocaml.org/cache)
∗ installed parsexp.v0.15.0
∗ installed sexplib.v0.15.1
Done.
```

```
changliu@TABLET8:~/root/cs3200/pa4-parser-drchangliu$ dune test
File "test/dune", line 2, characters 7-10:
2 |  (name pa4)
           ^^^
Testing `PA4'.
This run has ID `0WECWWSW'.

> [FAIL]        test            0   parse.
  [FAIL]        test            1   interp.
  [FAIL]        prog            0   run_fail.
  [FAIL]        prog            1   run_pass.

┌──────────────────────────────────────────────────────────────────────────────┐
│ [FAIL]        test            0   parse.                                     │
└──────────────────────────────────────────────────────────────────────────────┘
[exception] Todo(_)
            Raised at Pa4__Util.todo in file "lib/util.ml", line 39, characters 2-19
            Called from Pa4__Lib.(fun) in file "lib/lib.ml", line 208, characters 42-53
            Called from Alcotest_engine__Core.Make.protect_test.(fun) in file "src/alcotest-engine/core.ml", line 180, characters 17-23
            Called from Alcotest_engine__Monad.Identity.catch in file "src/alcotest-engine/monad.ml", line 24, characters 31-35

Logs saved to `/mnt/c/Users/msg4c/root/cs3200/pa4-parser-drchangliu/_build/default/test/_build/_tests/PA4/test.000.output'.
 ──────────────────────────────────────────────────────────────────────────────

Full test results in `/mnt/c/Users/msg4c/root/cs3200/pa4-parser-drchangliu/_build/default/test/_build/_tests/PA4'.
4 failures! in 0.017s. 4 tests run.
changliu@TABLET8:~/root/cs3200/pa4-parser-drchangliu$
```


After all required features are implemented, the test output should look like this:

```
changliu@TABLET8:~/root/cs3200/pa4-parser-drchangliu$ dune test
Testing `PA4'.
This run has ID `577X44Z2'.

  [OK]          test            0   free.
  [OK]          test            1   parse.
  [OK]          test            2   interp.
  [OK]          prog            0   run_fail.
  [OK]          prog            1   run_pass.

Full test results in `_build/default/test/_build/_tests/PA4'.
Test Successful in 0.021s. 5 tests run.
changliu@TABLET8:~/root/cs3200/pa4-parser-drchangliu$
```

## Code exploration using `utop`

To explore PA4 in utop, run `dune utop lib` and then `open Pa4__Lib;;` in utop.

Code you can try include:

```
sexp_of_string "(* (* 3 100) (+ 3 100))";;   (* good expression *)
sexp_of_string "(best * (* 3 a 100) (a + a 3 100 a))";;  (* Not a valid expression, but allowed by S expression *)
```

![](https://i.imgur.com/caZwnkh.png)
![](https://i.imgur.com/J3op781.png)

## LLM-Based Test Generation

You can extend **PA4 testing** using *LLM-generated cases* that probe both the parser and interpreter with fresh examples.

---

### Prerequisites

Ensure you have a valid API key set as environment variables(use either one):

```bash
# Option 1 — OpenAI
export OPENAI_API_KEY="your_openai_key_here"

# Option 2 — Google Gemini
export GEMINI_API_KEY="your_gemini_key_here"
```

If you previously set an API key and want to remove it (to skip LLM tests), run:
```
unset OPENAI_API_KEY
unset GEMINI_API_KEY
```

The LLM client and test logic are in: 
```
test/llm_client.ml 
test/llm_test.ml
```
Running LLM Test Generation To automatically fetch and run new parser/interpreter tests: 
```
dune build 
dune test 
```

### Cleaning the Build (Optional)

If you encounter stale build artifacts or strange test behavior, you can reset the build environment using:

```
dune clean
```
This command removes all files in the _build/ directory (including compiled binaries and cached test data).
Run it before rebuilding to ensure a completely fresh compilation.

When API keys are available, Llm_test will: Call the Gemini or OpenAI API via llm_client.ml Generate new JSON test cases for the parser and interpreter Log results to _build/default/test/test/llm_debug_pa4.log for inspection If no keys are set, these tests are skipped safely, and only local tests (parse, interp, run_fail, run_pass) are executed.

## Tips for Part 1 Parser

Consider the following functions `convert` and `convert_res`. They are incomplete examples that show how to process a S expression and construct an AST. Note that these two functions are similar in functionaly. One handles the raw Sexp; the other does that through Module `Result` for better exception handing.

You DO NOT need these functions for this PA. You can complete this PA using code with similar structures.

```
let convert (s : Sexp.t) : exp  =
  match s with
  | Atom x -> (match x with
               | "true" -> EVal (VBool true)
               | "false" -> EVal (VBool false)
               | _ -> match float_of_string_opt x with
                      | Some n -> EVal (VFloat n)  
                      | _ -> EIdent x
              )
  | List lst -> match lst with
              | [] -> EVal (VFloat 0.)
              | x :: xs ->
                 if List.length xs = 1 then
                   match x with
                   | Atom "not" -> EUnexp (UNot, EVal (VBool true))
                   | _ -> EVal (VFloat 1.)  (* Generating a Floating number 1 for anything else. This does not make much sense in content. Just showing how conversion can be done. *)
		 else
       		   EVal (VFloat 2.) (* Generating a Floating number 2 for list of any other length. This does not make much sense in content. Just showing how conversion can be done. *)
;;

(* Now, let's do the same with Module Result for better exception handling. *)
let rec convert_res (s : Sexp.t) : exp res  =
         match s with
         | Atom x -> (match x with
                      | "true" -> Ok (EVal (VBool true))
                      | "false" -> Ok (EVal (VBool false))
                      | _ -> match float_of_string_opt x with
                             | Some n -> Ok (EVal (VFloat n))
                             | _ -> Ok (EIdent x)
                     )
         | List lst -> match lst with
                     | [] -> Error "empty list"
                     | x :: xs ->
                        if List.length xs = 1 then
                          let* _ = convert_res @@ List.hd xs in
                          match x with
                          | Atom "not" -> Ok (EUnexp (UNot, EVal (VBool true)))
                          | _ -> Error ""
              else
                Error ""         
;;
```

In `utop`, you can try:

```
open Sexplib;;
Sexp.of_string "true";;
convert (Sexp.of_string "true");;
open Pa4__Util;;
let* e = sexp_of_string "true" in convert_res e ;;
```

```
utop # open Pa4__Util;;
─( 14:03:40 )─< command 16 >────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # let* e = sexp_of_string "true" in convert_res e ;;
- : (exp, string) result = Ok (EVal (VBool true))
─( 14:03:49 )─< command 17 >──────────────────────────
utop # convert (Sexp.of_string "(* (* 3 100) (+ 3 100))");;
- : exp = EVal (VFloat 2.)
─( 14:12:30 )─< command 26 >────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # 
```

```
utop # convert_res (Sexp.of_string "true");;
- : exp Pa4.Util.res = Ok (EVal (VBool true))
utop # convert (Sexp.of_string "true");;
- : exp = EVal (VBool true)
```

## Tips for Part 2 Interpreter

Note the use of `and` in mutually recursive functions. This is the big-step evaluation approach (ch9.3.5). You are free to use the single-step then multi-step evaluation approach (ch9.3.2/ch9.3.3) as well.

```
let rec interp (rho : env) (e : exp) : value res =
  match e with
  | EVal v -> Ok v
  | EIdent x -> lookup rho x
  | EUnexp (u, e1) -> interp_unexp rho u e1
  | _ -> todo (interp, rho, e) 
  (* | EBinexp (b, e1, e2) -> interp_binexp rho b e1 e2
  | EIte (e1, e2, e3) -> interp_ite rho e1 e2 e3
  | ELet (x, e1, e2) -> interp_let rho x e1 e2 *)

and interp_unexp (rho : env) (_ : unop) (e : exp) : value res =
    let* v = interp rho e in
    let* b = as_bool v in
    Ok (VBool (not b))
```

Here's how one can use `env` and `value`.
```
utop # upd init_env "x" (VFloat of 3.);;
Error: Syntax error: ')' expected, the highlighted '(' might be unmatched
─( 15:53:42 )─< command 5 >───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # upd init_env "x" (VFloat 3.);;
- : env = <fun>
─( 15:54:23 )─< command 6 >───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # let env1 = upd init_env "x" (VFloat 3.);;
val env1 : env = <fun>
─( 15:54:39 )─< command 7 >───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # let env2 = upd env1 "y" (VFloat 4.);;
val env2 : env = <fun>
─( 15:54:59 )─< command 8 >───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # lookup env1 "x";;
- : value Pa4.Util.res = Ok (VFloat 3.)
─( 15:55:21 )─< command 9 >───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # lookup env1 "y";;
- : value Pa4.Util.res = Error "y is unbound"
─( 15:55:42 )─< command 10 >──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # lookup env2 "y";;
- : value Pa4.Util.res = Ok (VFloat 4.)
─( 15:55:47 )─< command 11 >─────────────────────────────────────────────────────
```
