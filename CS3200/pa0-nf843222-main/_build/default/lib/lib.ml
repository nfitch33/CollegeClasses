(* 0. Write your name and OU ID (the part before the
   "@" in your email address) below:
  
   NAME: Nathaniel Fitch
   OU ID: 101093645
   Email: nf843222
 *)

open Alcotest
open Float
(*open Util*)
let e = 0.0001

(* 1. Define a function 'eucl_dist' that returns the Euclidean
   distance between two points (x1,y1) and (x2,y2). Look up Euclidean
   distance on Wikipedia if you forget how it's calculated. The OCaml
   floating point module is documented here:

   -[Float](https://ocaml.org/api/Float.html)

   Your function should satisfy the tests defined below. Note the use
   of 'epsilon_float' and '0.001', which we use here as tolerance
   values for comparing floating point values since they can't safely
   be compared for exact equality.
*)

let eucl_dist (x1 : float) (y1 : float) (x2 : float) (y2 : float) : float = 
 sqrt (((x2 -. x1) ** 2.0) +. ((y2 -. y1) ** 2.0))

(* Here we register some test cases to check that our 'eucl_dist'
   function behaves as expected. *)

let test_eucl_dist () =
  (check @@ float e) "zero" 0.0 (eucl_dist 0.0 0.0 0.0 0.0);
  (check @@ float e) "zero" 0.0 (eucl_dist 1.0 1.0 1.0 1.0);
  (check @@ float e) "sqrt(2)" (sqrt 2.0) (eucl_dist 0.0 0.0 1.0 1.0);
  (check @@ float e) "sqrt(2)" (sqrt 2.0) (eucl_dist 1.0 1.0 0.0 0.0);
  (check @@ float 0.001) "approx" (2.828) (eucl_dist (-1.0) (-2.0) (-3.0) (-4.0));
  (check @@ float 0.001) "approx" (2.828) (eucl_dist (-3.0) (-4.0) (-1.0) (-2.0))

(* 2. Define two functions, 'bool_and' and 'bool_or', that return,
   respectively, the Boolean conjunction or disjunction of their
   Boolean arguments b1 and b2.

   OCaml includes builtin infix operators "&&" and "||" -- use these
   only as a last resort (instead, try to encode conjunction and
   disjunction using just "if/then/else" and the Boolean literals
   "true" and "false").
*)

let bool_and (b1 : bool) (b2 : bool) : bool =
  if b1 then b2 else false

let test_bool_and () =
  (check bool) "FF" false (bool_and false false);
  (check bool) "FT" false (bool_and false true);
  (check bool) "TF" false (bool_and true false);
  (check bool) "TT" true  (bool_and true true)

let bool_or (b1 : bool) (b2 : bool) : bool =
  if b1 then true else b2

let test_bool_or () =
  (check bool) "FF" false (bool_or false false);
  (check bool) "FT" true  (bool_or false true);
  (check bool) "TF" true  (bool_or true false);
  (check bool) "TT" true  (bool_or true true)

(* 3. Using 'bool_and' and 'bool_or' as defined in exercise 2, define
   a function, maj, that returns the majority result of three boolean
   values b1, b2, and b3. For example, if b1 and b2 are true while b3
   is false, maj should return true.

   As in exercises 1 and 2, your function should pass all the test cases.
*)
  
let maj (b1 : bool) (b2 : bool) (b3 : bool) : bool =
  bool_or (bool_and b1 b2) (bool_or (bool_and b1 b3) (bool_and b2 b3))

let test_maj () =
  (check bool) "FFF" false (maj false false false);
  (check bool) "FFT" false (maj false false true);
  (check bool) "FTF" false (maj false true false);
  (check bool) "FTT" true  (maj false true true);
  (check bool) "TFF" false (maj true false false);
  (check bool) "TFT" true  (maj true false true);
  (check bool) "TTF" true  (maj true true false);
  (check bool) "TTT" true  (maj true true true)

(* 4. Modify the following function, 'hello_world', so that it passes
   its test case. Note that there are multiple correct solutions to
   this exercise.
*)

let hello_world : string =
  let s1 = "hello\n" in
  let s2 = " world!! :-)" in
  s1 ^ s2


let test_hello_world () =
  (check string) "equal" "hello\n world!! :-)" (hello_world)

(* 5. Define a function 'fib' that computes the nth fibonacci
   number. Recall that the fibonacci sequence can be defined by the
   following set of recursive equations:

   fib(0) = 0
   fib(1) = 1
   fib(n) = fib(n - 2) + fib(n - 1), when n >= 2

   Note the use of the 'rec' keyword telling OCaml that we intend to
   be able to refer to 'fib' within its own body.
*)

let rec fib (n : int) : int =
  if n = 0 then 0
  else if n = 1 then 1
  else fib (n - 1) + fib (n - 2)

let test_fib () =
  (check @@ list int) "equal" [0; 1; 1; 2; 3; 5; 8; 13; 21; 34; 55; 89; 144; 233]
    (List.init 14 fib)
