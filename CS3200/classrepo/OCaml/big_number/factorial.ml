open Big_int

(**** Version 1: The input is a big_int. ****)

let factorial : big_int -> big_int = fun num ->
     let rec factTR : big_int -> big_int -> big_int = fun n acc ->
          if gt_big_int n (big_int_of_int 0)
          then factTR 
            (sub_big_int n (big_int_of_int 1))  (* n - 1 *)
            (mult_big_int acc n)
          else acc
     in
          factTR num (big_int_of_int 1)
;;

let fac = factorial (big_int_of_int 50) in
  print_endline ("The big number factorial of big_int 50 is: " ^ string_of_big_int fac);

let fac = factorial (big_int_of_int 500) in
  print_endline ("The big number factorial of big_int 500 is: " ^ (string_of_big_int fac));

let fac = factorial (big_int_of_int 5000) in
  print_endline ("The big number factorial of big_int 5000 is: " ^ (string_of_big_int fac));
;;


(**** Version 2: The input is a simple int. ****)

let factorial : int -> big_int = fun num ->
  let rec factTR : int -> big_int -> big_int = fun n acc ->
       if n > 0
       then factTR (n - 1) (mult_big_int acc (big_int_of_int n))
       else acc
  in
       factTR num (big_int_of_int 1)
;;

let fac = factorial 5 in
  print_endline ("The big number factorial of 5 is: " ^ string_of_big_int fac);

let fac = factorial 50 in
  print_endline ("The big number factorial of 50 is: " ^ string_of_big_int fac);

let fac = factorial 500 in
  print_endline ("The big number factorial of 500 is: " ^ string_of_big_int fac);

let fac = factorial 5000 in
  print_endline ("The big number factorial of 5000 is: " ^ string_of_big_int fac);

let fac = factorial 50000 in
  print_endline ("The big number factorial of 50000 is: " ^ string_of_big_int fac);

let fac = factorial 500000 in
  print_endline ("The big number factorial of 50000 is: " ^ string_of_big_int fac);

