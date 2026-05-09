open Midterm
open Printf

let _ = printf "\n-----Grading with external test cases.-----\n" 
;;

(* There will be a lot more test cases here for all problems. *)
print_endline "\n--Problem 1:";
;;

(* External tests for Problem 1 *)
try
  let result = find (fun x -> x > 10) [1; 5; 12; 8] in
  if result = 12 then print_endline "<PASS> external test find >10"
  else print_endline "!FAIL! external test find >10"
with _ ->
  print_endline "!FAIL! Exception in external test for Problem 2"
;;

print_endline "\n--Problem 2:";
(* External tests for Problem 2 *)
try
  let three = S (S (S O)) in
  let two = S (S O) in
  let one = S O in
  if substract three two = one then
    print_endline "<PASS> external test substract 3-2"
  else
    print_endline "!FAIL! external test substract 3-2"
with _ ->
  print_endline "!FAIL! Exception in external test for Problem 3"
;;
print_endline "\n--Problem 3:";
(* External tests for Problem 3 *)
try
  let t = O (P ZZ) in
  let result = inc t in
  if to_int result = 4 then
    print_endline "<PASS> external test inc 3"
  else
    print_endline "!FAIL! external test inc 3"
with _ ->
  print_endline "!FAIL! Exception in external test for Problem 4"
;;

print_endline "";
print_endline "===End of CS3200 midterm exam Grading===\n\n";
