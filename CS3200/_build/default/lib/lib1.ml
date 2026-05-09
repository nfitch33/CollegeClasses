(************************************************************************
0. Fill your name and OU ID or PID on the line below:
*)
let name = "Nathaniel Fitch";;
let id = "p101093645";;
let _ = Printf.printf "\n-----NAME: %s ID:%s -----\n" name id;;

open Alcotest
open Util

(** PART I (Lists):

   1. (10 pts) As a warmup, define a function 'len' that computes the
   length of a list, producing an int result.

   NOTE: Don't use any library functions (like 'List.length') in this
   exercise. Instead, use pattern matching and recursion on the list
   to calculate the length. *)

let rec len (l : 'a list) : int =
  match l with
  | [] -> 0
  | _ :: tail -> 1 + len tail

(** The following tests check that your 'len' function behaves as
   expected on a few specific inputs. *)
let () = add_test "len" @@
  fun _ ->
    (check int) "len [0] = 1" (len [0]) 1;
    (check int) "len [] = 0" (len []) 0;
    (check int) "len [1; 2; 3; 4; 5] = 5" (len [1; 2; 3; 4; 5]) 5;
    (check int) "len [1; 2] = 2" (len [1; 2]) 2;
    (check int) "len [false] = 1" (len [false]) 1;
    (check int) "len [[\"heimerdinger\"]] = 1" (len [["heimerdinger"]]) 1

(** 2. (10 pts) Define a function 'append' that takes two 'a list
   arguments l1 and l2, for any type 'a, and returns the concatenation
   of the two lists. That is, your function should return a single
   list that contains, first, all the elements of l1, then all the
   elements of l2. *)

let rec append (l1 : 'a list) (l2 : 'a list) : 'a list =
  match l1 with
  | [] -> l2
  | head :: tail -> head :: append tail l2

let () = add_test "append" @@
  fun _ ->
    (check @@ list int) "[] ++ [] = []" [] (append [] []);
    (check @@ list char) "['a'] ++ [] = ['a']" ['a'] (append ['a'] []);
    (check @@ list (float epsilon_float)) "[1.0] ++ [] = [1.0]" [1.0] (append [1.0] []);
    (check @@ list int) "[1; 2] ++ [3] = [1; 2; 3]" [1; 2; 3] (append [1; 2] [3]);
    (check @@ list (list int)) "[[]] ++ [[]] = [[]; []]" [[]; []] (append [[]] [[]])

(** In addition to handwritten test cases like those above, we will
   sometimes use QCheck to test general properties that are expected
   to hold of your code. For example, the following test checks that
   the empty list is the left identity wrt. 'append': *)

(* [∀ l, [] ++ l = l] *)
let () = add_qcheck @@
  QCheck.(Test.make ~name:"append_left_identity" ~count:200
            (small_list int)
            (fun l -> append [] l = l))


(** QCheck works by randomly generating values (lists of integers in
   this case) and checking that a given predicate evaluates to true
   for all of them. Here (above) we told QCheck to generate 200 random
   lists using the generator 'small_list int' (specifying how random
   lists should be generated), and to check that the predicate 'fun l
   -> append [] l = l' always evaluates to true when applied to them.

   You're free to experiment with QCheck, but you aren't required to
   write any QCheck tests. We provide tests to help guide your
   implementation, and to help us with grading. Your implementation
   should pass all of the tests that we provide.

   The file '/test/pa1.ml' contains more QCheck tests that your
   'append' and other functions are expected to pass. *)

(** 3. (10 pts) Define a function 'snoc' that links a value of type 'a
   onto the *end* of a 'a list. For example: snoc(1, [3; 2]) should
   result in [3; 2; 1]. 'snoc' is the reverse of 'cons'.

   HINT: Structure your program, as you presumably did in exercises 1
   and 2, as a case analysis on the input list l. Think recursively in
   the case when l is a cons(f, r), with head or front element f and
   tail or rest r. What's a recursive way in which to move the new
   element "a" toward the end of the list, while maintaining the
   correct structure of the list up to that point? *)

let rec snoc (a : 'a) (l : 'a list) : 'a list =
  match l with
  | [] -> [a]
  | head :: tail -> head :: snoc a tail

let () = add_test "snoc" @@
  fun _ ->
    (check @@ list int) "snoc 1 [3; 2] = [3; 2; 1]" [3; 2; 1] (snoc 1 [3; 2]);
    (check @@ list char) "snoc 'z' [] = ['z']" ['z'] (snoc 'z' []);
    (check @@ list bool) "snoc false [true; false] = [true; false; false]"
      [true; false; false] (snoc false [true; false])


(** 4. (20 pts) Using your implementation of snoc in #3, define a
   function 'rev' that reverses a list. For example, rev [1; 2; 3]
   should result in [3; 2; 1]. *)

let rec rev (l : 'a list) : 'a list =
  match l with
  | [] -> []
  | head :: tail -> snoc head (rev tail)

let () = add_test "rev" @@
  fun _ ->
    (check @@ list int) "rev [1; 2; 3] = [3; 2; 1]" [3; 2; 1] (rev [1; 2; 3]);
    (check @@ list char) "rev [] = []" [] (rev []);
    (check @@ list int) "rev [1] = [1]" [1] (rev [1]);
    (check @@ list bool) "rev [false; true] = [true; false]"
      [true; false] (rev [false; true])

(** 5. (20 pts) Using your append function from #2, define a function
   'flatten' that takes a list of lists and flattens it to a single
   list. For example, flatten [[1]; []; [2; 3]] should result in the
   list [1; 2; 3]. *)

let rec flatten (l : 'a list list) : 'a list =
  match l with
  | [] -> []
  | head :: tail -> append head (flatten tail)

let () = add_test "flatten" @@
  fun _ ->
    (check @@ list int) "flatten [[1]; []; [2; 3]] = [1; 2; 3]"
      [1; 2; 3] (flatten [[1]; []; [2; 3]]);
    (check @@ list char) "flatten [[]] = []" [] (flatten [[]]);
    (check @@ list (list int)) "flatten [[[]]] = [[]]" [[]] (flatten [[[]]]);
    (check @@ list int) "flatten [[1; 2; 3]] = [1; 2; 3]"
      [1; 2; 3] (flatten [[1; 2; 3]]);
    (check @@ list bool) "flatten [[false]] = [false]"
      [false] (flatten [[false]]);
    (check @@ list bool) "flatten [[false]; []] = [false]"
      [false] (flatten [[false]; []])


(** 6. (30 pts) Define a function 'isort' that uses the insertion sort
   algorithm to sort a list of integers. *)

let rec isort (l : int list) : int list =
  let rec insert (a : int) (xs : int list) : int list =
    match xs with
    | [] -> [a]
    | head :: tail ->
        if a <= head then a :: xs
        else head :: insert a tail
  in
  match l with
  | [] -> []
  | head :: tail -> insert head (isort tail)

let () = add_test "isort" @@
  fun _ ->
    (check @@ list int) "isort [3; 2; 1] = [1; 2; 3]" [1; 2; 3] (isort [3; 2; 1]);
    (check @@ list int) "isort [] = []" [] (isort []);
    (check @@ list int) "isort [1] = [1]" [1] (isort [1]);
    (check @@ list int) "isort [3; 5; -7; 1; 0; 200] = [-7; 0; 1; 3; 5; 200]"
      [-7; 0; 1; 3; 5; 200] (isort [3; 5; -7; 1; 0; 200])

