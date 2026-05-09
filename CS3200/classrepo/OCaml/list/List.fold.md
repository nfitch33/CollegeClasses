Scenario: There is a list of strings representing numbers. Find the sum of all even numbers after doubling them.

```ocaml
let string_to_int s = int_of_string s

(* Filter function to keep only even numbers (as strings) *)
let keep_even_strings lst =
  List.filter (fun s -> string_to_int s mod 2 = 0) lst

(* Map function to convert strings to doubled integers *)
let double_strings_to_ints lst =
  List.map (fun s -> 2 * string_to_int s) lst

(* Fold function to sum the list of integers *)
let sum_list lst =
  List.fold_left (+) 0 lst

let example_list = ["1"; "2"; "3"; "4"; "5"]

(* Filtering even strings *)
let even_strings = keep_even_strings example_list

(* Doubling strings to integers *)
let doubled_ints = double_strings_to_ints even_strings

(* Summing the doubled integers *)
let total_sum = sum_list doubled_ints

(* Print the result *)
let () = print_endline (string_of_int total_sum)
```
