# Chapter 3. Data and Types - Highlights

* Lists do not have a way to access the i-th element efficiently at O(1). (OCaml does have arrays. (Ch7.3) )
* Lists are immutable. 
* How to generate or construct a list. Tail recursion for extra long lists. ([example.](list.ipynb))
* How to compute the length or the sum of a list.
* `List.init` takes a function as a parameter
* `fun` and `function` are slightly different. See https://v2.ocaml.org/manual/expr.html and https://stackoverflow.com/questions/1604270/what-is-the-difference-between-the-fun-and-function-keywords

* Like records, tuples are a composite of other types of data. But instead of naming the components, they are identified by position. 
* A tuple with two components is called a pair. A tuple with three components is called a triple.
* Tuple types are written using a new type constructor *, which is different than the multiplication operator. 

* How to make tree functions tail recursive? ( CPS (Continuation Passing Style).)

* The math behind lists - set theory:
  * Union A ∪ B
  * Intersection A ∩ B
  * Cartesian product A × B = {(a, b) : a ∈ A and b ∈ B}
  * Disjoint union (as defined in this class) A ∪⁺ B = {(0, x) | x ∈ A} ∪ {(1, y) | y ∈ B}

* The following OCaml type has how many distinct values?

```
type typeSimple = bool
```

```
type typeA =
  | BoolCondition1 of bool
  | BoolCondition2 of bool
```
(* 4 = 2+2 *)
```
type typeB =
  | BoolCondition1 of bool
  | BoolCondition2 of bool * bool
```
(* 6 = 2+4 *)

* injective functions
  * A function f : A → B is injective iff ∀ x y ∈ A, f(x) = f(y) ⇒ x = y
* [surjective functions](https://www.mathsisfun.com/sets/injective-surjective-bijective.html)
  * A function f : A → B is surjective iff ∀ y ∈ B, ∃ x ∈ A, f(x) = y
* bijective = both injective and surjective

	
