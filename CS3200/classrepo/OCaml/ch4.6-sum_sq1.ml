(* https://cs3110.github.io/textbook/chapters/hop/pipelining.html
4.6. Piplelining example: Sum of Squares of the numbers from 0 to n
*)

let sum_sq n =
  let rec loop i sum =
    if i > n then sum
    else loop (i + 1) (sum + i * i)
  in loop 0 0
in
  print_int(sum_sq 1);
  print_string("\n");
  print_int(sum_sq 2);
  print_string("\n");
  print_int(sum_sq 3);
  print_string("\n");
  print_int(sum_sq 4);
  print_string("\n");
  print_int(sum_sq 5);
  print_string("\n");
  print_int(sum_sq 6);
  print_string("\n");
;;  
  
let rec ( -- ) i j = if i > j then [] else i :: i + 1 -- j
let square x = x * x
let sum = List.fold_left ( + ) 0

let sum_sq n =
  0 -- n              (* [0;1;2;...;n]   *)
  |> List.map square  (* [0;1;4;...;n*n] *)
  |> sum              (*  0+1+4+...+n*n  *)
;;                      
print_int(sum_sq 1);
print_string("\n");
print_int(sum_sq 2);
print_string("\n");
print_int(sum_sq 3);
print_string("\n");
print_int(sum_sq 4);
print_string("\n");
print_int(sum_sq 5);
print_string("\n");
print_int(sum_sq 6);
print_string("\n")
