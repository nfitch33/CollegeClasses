(* Example usage of List.for_all and List.exists *)
(* https://ocaml.org/manual/5.2/api/List.html    *)

let is_even n = n mod 2 = 0

let example_list = [1; 2; 3; 4; 5; 6]

let result = List.for_all is_even example_list

let () = print_endline (string_of_bool result)
;;
result
;;

List.for_all is_even [2; 4; 8]
;;

List.exists is_even [1; 2; 3]
;;
List.exists is_even [1; 5; 3]
;;

