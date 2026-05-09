(* Load the Zarith library in toplevel with this:
#require "zarith";;
*)


(* Open the Z module for integers *)
open Z;;

(* Creating big integers *)
let big_int1 = Z.of_string "123456789012345678901234567890";;
let big_int2 = Z.of_string "987654321098765432109876543210";;

(* Performing arithmetic operations *)
let sum = Z.add big_int1 big_int2;;
let product = Z.mul big_int1 big_int2;;

(* Converting back to string for display *)
print_endline ("Sum: " ^ Z.to_string sum);;
print_endline ("Product: " ^ Z.to_string product);;
