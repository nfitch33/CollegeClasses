(* Open the Num module *)
open Num;;

(* Creating big integers *)
let big_num1 = num_of_string "123456789012345678901234567890";;
let big_num2 = num_of_string "987654321098765432109876543210";;

(* Performing arithmetic operations *)
let sum = add_num big_num1 big_num2;;
let difference = sub_num big_num2 big_num1;;
let product = mult_num big_num1 big_num2;;
let quotient = div_num big_num2 big_num1;;

(* Converting back to string for display *)
print_endline ("Sum: " ^ string_of_num sum);;
print_endline ("Difference: " ^ string_of_num difference);;
print_endline ("Product: " ^ string_of_num product);;
print_endline ("Quotient: " ^ string_of_num quotient);;
