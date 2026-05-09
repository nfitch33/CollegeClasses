## Chapter 2. The Basics of OCaml - Highlights

* Two equality operators in OCaml, `=` and `==`, with corresponding inequality operators `<>` and `!=`. Operators `=` and `<>` examine structural equality whereas `==` and `!=` examine physical equality. 

* Scope
  * Shadowing is not mutable assignment.

* If expressions
* Let expressions

* Anonymous functions (lambda expressions, a term that comes from the lambda calculus, which is a mathematical model of computation.)
* Pipelines
* Partial application of functions

* 2.4.2 Anonymous functions are also called lambda expressions

* 2.4.10. [Tail Recursion](TailRecursion.ipynb)

* 2.4.1 Mutually recursive functions can be defined with the and keyword:

*  structural recursion vs. generative (non-structural) recursion.

```
let f x = x + 8
let g = f

let f' x = x + 8

(* Physical equality *)
let same_function = (f == g)  (* This will be true *)
let different_functions = (f == f')  (* This may be false *)

(* Structural equality *)
let _ = (f = g)  (* This will raise Exception: (Invalid_argument "compare: functional value") *)
```
