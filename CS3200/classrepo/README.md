# CS3200 Organization of Programming Languages

* [CS3200 Syllabus](CS3200.md)
* [Introduction](Introduction.md)

### OCaml Books

[Michael R. Clarkson et al. OCaml Programming: Correct + Efficient + Beautiful](https://cs3110.github.io/textbook/cover.html) (from Cornell) ([PDF](https://cs3110.github.io/textbook/ocaml_programming.pdf)), Fall 2025 edition.

Minsky, Yaron, Anil Madhavapeddy, and Jason Hickey. [Real World OCaml: Functional programming for the masses](https://dev.realworldocaml.org/index.html). O'Reilly, 2013.

[Developing Applications With Objective Caml](https://caml.inria.fr/pub/docs/oreilly-book/), O'Reilly, 2000. (Translated from French, a little dated, but more technically detailed.)

#### Related OCaml Links
* OCaml API documentation: https://v2.ocaml.org/api/
* OCaml keywords: https://v2.ocaml.org/releases/4.07/htmlman/manual049.html
* Dune: https://dune.readthedocs.io/en/stable/quick-start.html
* OCaml examples: https://o1-labs.github.io/ocamlbyexample/

#### Real World OCaml
* https://www.janestreet.com/technology/
* [Meta/Facebook Infer](https://github.com/facebook/infer/tree/main/infer/src/base)
* https://github.com/logseq/logseq (Parser mldoc)


### Key Concepts

+: Better or more cleanly designed in OCaml or functional languages in general.

~: About the same in OCaml versus in C/C++/Java/etc. No particular advantages of the OCaml version.

-: More cumbersome or clumsy in OCaml than in Java/C++, perhaps intentially designed this way.

* List (+)
  * Association lists (lists of pairs (tuples))
* Tree (Red Black Tree, Binary Search Tree) (~)
* Recursive functions, recursive types (trees), recursive values (sequences-ch8.4)
* Tail Recursion and Recursion with Memoization (ch8.5)
* Sequence, Lazy evaluation (+) (built-in OCaml keyword `lazy`)
* Map, filter, fold (+)
* How to handle big integer
* A **functional data structure** is one that does not make use of mutability. (ch5.6)
* Hashtable
* Exception handling (with try/with (~); with match (+); with maybe monad (++))
* Option type (ch3.7) (Some, None) (+) 
* Module Result (pa4-parser) (Ok, Error (with a message)) (+)
* Pattern matching (+)
* Type inference (+)
* Parser construction, AST (Abstract Syntax Tree) (+)
* Expression evaluation (+)
* Memoization (ch8 data structure)
* Reference (-)
* Array, loop (~)
* Modules (~)
* Monads (++)
* Operator overloading (e.g. *, *.) (-)
* Immutable data structure (+)
* Functor (+)
* Parser generator (~)
  * The substitution model (ch9.3) and the environment model (ch9.4)
  * Big vs. small step evaluation
  * Syntactic sugar, Desugaring (ch3.1; ch9.3) (+)
* Constraint-based type inference ([ch9.6.3 constraint unification](https://cs3110.github.io/textbook/chapters/interp/inference.html#solving-constraints))
  * OCaml is statically typed (like Java, unlike JavaScript)
  * OCaml is implicitly typed (unlike Java)
* Polymorphism and mutability (weak type) (ch9.6.6)

### Related CodeWars Katas

* (7 Kyu) Likes Vs Dislikes (match): https://www.codewars.com/kata/62ad72443809a4006998218a
* (8 Kyu) Abbreviate a Two Word Name (list): https://www.codewars.com/kata/57eadb7ecd143f4c9c0000a3
* (7 Kyu) Remove Elements from a List (filter): https://www.codewars.com/kata/563089b9b7be03472d00002b
* (6 Kyu) Back and forth then reverse (list efficiency and tail recursion): https://www.codewars.com/kata/60cc93db4ab0ae0026761232
* (6 Kyu) A disguised sequence (I) (HashTable, Cached recursive functions, big integer in Num) https://www.codewars.com/kata/563f0c54a22b9345bf000053
* (2 Kyu) A Simple Postfix Language https://www.codewars.com/kata/55a4de202949dca9bd000088/
* (1 Kyu) Tiny Three-Pass Compiler https://www.codewars.com/kata/5265b0885fda8eac5900093b




### OCaml installation

```
sudo apt install ocaml opam
opam init
opam install dune utop
# Be sure to create an opam switch
opam switch create cs3200 ocaml-base-compiler.5.0.0
eval $(opam env) # Run opam env directly once to see what's the output
which ocamlc     # To check where the compiler is located
opam switch      # to check the switches
opam install dune utop qcheck alcotest qcheck-alcotest ounit
                 # It does not hurt if installed packages show up again in a `opam install` command
```
After that, you can compile `hello.ml` by running `ocamlc hello.ml` and then `./a.out`.

Or, if you have the source code of an OCaml project, you can compile and run/test a project, you can run `dune test`.

To clear the temporary result and run `dune test` again, one can run `dune clean`.

#### Compiling and running OCaml code:
* `ocaml`/`ocamlc` (The most direct way. All other approaches use ocaml/ocamlc as an underlying tool.)
* `utop` (interactive shell)
* `dune build`/`dune test` (A project management tool for large and small projects.)
* `jupyter notebook` (an intertive interface in web browsers, Visual Studio Code, and Github Codespaces)

* To try simple code quickly, visit https://try.ocamlpro.com/, [OnlineGDB](https://onlinegdb.com/JbttC0P3p) or [https://onecompiler.com/ocaml/](https://onecompiler.com/ocaml/42sfvsjem)

#### Jupyter installation

* https://ocaml.org/p/jupyter/latest
* https://akabe.github.io/ocaml-jupyter/

As of 2024.9, OCaml 5.0 still doesn't work with Jupyter. Use 4.13.0.

To install: (Make sure to follow instructions in the links above, which includes additional commands such as `pip install jupyter`.)
```
opam switch create cs3200.4.13 ocaml-base-compiler.4.13.0
opam install ocaml-lsp-server jupyter
ocaml-jupyter-opam-genspec
jupyter kernelspec install --user --name "ocaml-jupyter-$(opam var switch)" "$(opam var share)/jupyter"
```

To run
```
jupyter notebook
```

#### To compile or directly run the sample source code files:

```
@drchangliu ➜ /workspaces/examples/ocaml (main) $ ocamlc hello.ml 
@drchangliu ➜ /workspaces/examples/ocaml (main) $ ./a.out
Hello World!
from CompSci3200
from CS 3200
@drchangliu ➜ /workspaces/examples/ocaml (main) $ ocaml fib.ml 
55
@drchangliu ➜ /workspaces/examples/ocaml (main) $ ocamlc fib.ml
@drchangliu ➜ /workspaces/examples/ocaml (main) $ ./a.out
55

```

#### To compile OCaml code with additional modules:
```
ocamlfind ocamlc -o test -package oUnit -package num -linkpkg -g pa4hash.ml
ocamlfind ocamlc -o promises -package lwt -package lwt.unix -thread -linkpkg -g promises.ml
```


#### Operators

* `=` and `<>` examine structural equality. 
* `==` and `!=` examine physical equality.
* `[]`  The empty list is written as [] and is pronounced “nil”.
* `::` The double-colon operator is pronounced “cons”, a name that comes from an operator in Lisp that constructs objects in memory.

The apostrophe (') in OCaml is used to prefix a type variable. Type variables are placeholders for any given type. 
* 'a: pronounced as alpha
* 'b: pronounced as beta
* 'c: pronounced as "gamma"
* 'd: pronounced as "delta"
* 'e: pronounced as "epsilon"
* 'f: pronounced as "zeta"
* 'g: pronounced as "eta"

* In variable name (a'), the apostrophe is often pronounced as "prime." So, f'(x) would be read as "f prime of x." It means derivative.
* In the case of matrix operation, the apostrophe is often pronounced as "transpose." Thus, A' would be read as "A transpose."

Array contents can be changed using the `<-` operator. (Ch7.3)

#### Utility functions


```
let rec ( -- ) i j = if i > j then [] else i :: i + 1 -- j  (* This one is not a tail-recursive implementation. *)
let square = fun x -> x * x
let even n = n mod 2 = 0 
let triple n = n mod 3 = 0
let quadruple n = n mod 4 = 0
let odd = fun n -> n mod 2 = 1 
let not_in x lst = List.for_all ((<>) x) lst  (* not in *)
let ( --- ) x lst = List.for_all ((<>) x) lst  (* not in *)
let is_in x lst = List.exists ((=) x) lst (* in *)
let ( -+- ) x lst = List.exists ((=) x) lst (* in *)
```
