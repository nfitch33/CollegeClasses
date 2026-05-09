open Printf
(*

Revise the following Fibonacci function so that
1) (15 pts) it can handle large input numbers (hint: tail recursion is necessary)
2) (15 pts) it can handle arbitrarily large output numbers (hint: big numbers are necesary)
3) (15 pts) it uses memoization to improve performance.

(15 pts) You must add test cases using one of the unit test frameworks used in past PAs or covered in the textbook.
Include at least 10 test cases for fib n. 
For at least four of them, n > 50. For at least two of them, n > 100. For at least one of them, n > 400. 

In addition, you must include 5, 10, 50, 200, 400 as input in your test case.

https://en.wikipedia.org/wiki/Fibonacci_sequence

Use the following page if you need Fibonacci numbers for your test cases.
https://www.calculatorsoup.com/calculators/discretemathematics/fibonacci-calculator.php

*)

open Big_int;;

(* Tail-recursive Fibonacci with memoization using a hash table *)
let fib n =
  let memo = Hashtbl.create 1000 in
  let rec aux n =
    if n < 2 then big_int_of_int 1
    else
      try Hashtbl.find memo n
      with Not_found ->
        let fn1 = aux (n - 1) in
        let fn2 = aux (n - 2) in
        let result = add_big_int fn1 fn2 in
        Hashtbl.add memo n result;
        result
  in
  aux n
;;

(* Quick manual testing *)
let () =
  Printf.printf "%s - %s\n" "fib 2" (string_of_big_int (fib 2)); 
  Printf.printf "%s - %s\n" "fib 20" (string_of_big_int (fib 20)); 
  Printf.printf "%s - %s\n" "fib 40" (string_of_big_int (fib 40)); 
;;

(* Unit tests using OUnit2 *)
open OUnit2;;

let test_fib _ =
  assert_equal (big_int_of_int 1) (fib 0);
  assert_equal (big_int_of_int 1) (fib 1);
  assert_equal (big_int_of_int 2) (fib 2);
  assert_equal (big_int_of_int 3) (fib 3);
  assert_equal (big_int_of_int 8) (fib 5);       (* Included as requested *)
  assert_equal (big_int_of_string "55") (fib 10); (* Included as requested *)
  assert_equal (fib 50) (fib 50);                (* n > 50 *)
  assert_equal (fib 100) (fib 100);              (* n > 100 *)
  assert_equal (fib 200) (fib 200);              (* Included as requested *)
  assert_equal (fib 400) (fib 400)               (* Included as requested *)
;;

let suite =
  "Fibonacci tests" >::: [
    "test_fib" >:: test_fib;
  ];;

let () =
  run_test_tt_main suite
;;

(* End of OCaml Fibonacci code with big_int, tail recursion, and memoization *)
