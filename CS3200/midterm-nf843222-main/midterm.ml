open Printf

(*************************************************
0) Fill in your name and PID on the line below.
*)

let _ = printf "\n-----NAME: %s  PID: %s -----\n" 
  "Nathaniel Fitch" "P101093645"
;;

let todo (type t) (x : t) : 'a =
  let module M = struct exception Todo of t end in
  raise @@ M.Todo x
;;


(********************************************************
1) Implement a function find that returns the first element 
of the list l that satisfies a predicate f. If the element 
is not found, raise exception Not_found. You can use all 
functions already implemented in PA1. 
You cannot use OCaml built-in List operations.*)


(* Question 1 is implemented here *)
let rec find f lst =
  match lst with
  | [] -> raise Not_found
  | head :: tail ->
      if f head then head
      else find f tail
;;
print_endline "\n--Problem 1:";
;;

let rec find f lst =
  todo (f, lst);;

let odd x = x mod 2 = 1;;

try
  let result = find odd [0; 1; 2; 3; 4; 5] in
    if result = 1 then print_endline "PASS test case [0; 1; 2; 3; 4; 5] odd"
    else print_endline "!FAIL! test case [0; 1; 2; 3; 4; 5] odd"
with
  | Not_found -> print_endline "!FAIL! with Not_found"
  | _ -> print_endline "!FAIL! Not Implemented"
;;

try
  let result = find odd [0; 2; 4; ] in
    print_int result;
    print_endline "!FAIL! [0; 2; 4] odd" ;
with
  | Not_found -> print_endline "PASS with Not_found"
  | _ -> print_endline "!FAIL! Not Implemented"
;;

(**********************************************
2) On top of PA2, implement subtraction.

let rec subtract (n : nat) (m : nat) : nat =
  todo (subtract, n, m) (* replace with your solution *)
*)

type nat =
  | O
  | S of nat

let rec subtract (n : nat) (m : nat) : nat =
  match (n, m) with
  | (O, _) -> O              
  | (n, O) -> n            
  | (S n', S m') -> subtract n' m' 
;;


print_endline "\n--Problem 2:";;

  

(* Testing boilerplate (feel free to ignore). *)
let rec string_of_nat : nat -> string = function
  | O -> "O"
  | S n' -> "S " ^ string_of_nat n'
let rec nat_of_int : int -> nat = function
  | n when n <= 0 -> O
  | n -> S (nat_of_int (n - 1))

let one   = S O
let two   = S one
let three = S two
let four  = S three
let five  = S four
let six   = S five

let rec substract (n : nat) (m : nat) : nat =
  todo (substract, n, m) ;;

try
    if substract five three <> two then
      printf "!FAIL! - substract test case 1.\n"
with
  | _ -> printf "!FAIL! Exception caught.\n"
;;
  
(********************************************************
3) Ternary Increment
 *
 * Given the following ternary number definition, implement a function inc
 * that will add one to the parameter, which is a ternary, and
 * return the sum as a ternary.
 *
 * You CANNOT do it by converting the ternary to int,
 * increment it, and converting it back to ternary.
 ********************************************************)


print_endline "\n--Problem 3:";
;;

type ternary =
  | NN (* -1 *)
  | ZZ (* 0 *)
  | PP (* +1 *)
  | N of ternary (* t*3-1 *)
  | O of ternary (* t*3 *)
  | P of ternary (* t*3+1 *)

(* Following functions are provided for your convenience during testing and debugging *)
(* Normalize to canonical form by removing leading zeros *)
let rec normalize = function
  | O NN -> NN
  | O ZZ -> ZZ
  | O PP -> PP
  | O t -> (match normalize t with
            | ZZ -> ZZ
            | t' -> O t')
  | N t -> N (normalize t)
  | P t -> P (normalize t)
  | t -> t

(* Convert ternary to integer *)
let rec to_int = function
  | NN -> -1
  | ZZ -> 0
  | PP -> 1
  | N t -> 3 * to_int t - 1
  | O t -> 3 * to_int t
  | P t -> 3 * to_int t + 1

(* Convert integer to ternary *)
let rec of_int n =
  if n = 0 then ZZ
  else if n = 1 then PP
  else if n = -1 then NN
  else
    let q, r = 
      if n > 0 then
        ((n + 1) / 3, (n + 1) mod 3 - 1)
      else
        ((n - 1) / 3, (n - 1) mod 3 + 1)
    in
    normalize (match r with
      | -1 -> N (of_int q)
      | 0 -> O (of_int q)
      | 1 -> P (of_int q)
      | _ -> failwith "impossible")


let rec inc t =
  todo (inc, t)

let rec inc t =
  match t with
  | NN -> ZZ
  | ZZ -> PP
  | PP -> O PP      
  | N x ->            
      (match inc x with
       | NN -> O NN
       | ZZ -> O ZZ
       | PP -> O PP
       | N x' -> N (inc x')  
       | O x' -> O (inc x')
       | P x' -> P (inc x'))
  | O x ->             
    P x
  | P x ->            
    O (inc x)
;;
;;


try
  let result = inc NN in
  if to_int result = 0 then print_endline "PASS inc -1"
  else print_endline "!FAIL! inc -1"
with
  | _ -> print_endline "!FAIL! Not Implemented"
;;

try
  let result = inc PP in
  if to_int result = 2 then print_endline "PASS inc 1"
  else print_endline "!FAIL! inc 1"
with
  | _ -> print_endline "!FAIL! Not Implemented"
;;

try
  let result = inc (O(O(PP))) in
  if to_int result = 10 then print_endline "PASS inc 9"
  else print_endline "!FAIL! inc 9"
with
  | _ -> print_endline "!FAIL! Not Implemented"
;;

print_endline "---End of CS3200 midterm exam self-testing---\n\n";
