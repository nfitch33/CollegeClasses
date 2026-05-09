(* This Hello World program shows several styles of OCaml printing and string/int manipulation. *)

let x : int = 3200 in
let _ = print_string("Hello World!\n") in
let _ = print_string("from CompSci") in
let _ = print_int(x) in
  print_string("\n");
  print_string("from CS " ^ string_of_int x ^ "\n")

(*
Here's how you can run it in utop.

https://github.com/user-attachments/assets/6437d4a3-cf75-4d49-8be7-bfa7c55aee28

*)
