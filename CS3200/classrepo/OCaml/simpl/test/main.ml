open OUnit2
open Interp
open Ast
open Main
open Printf


(** [make_i n i s] makes an OUnit test named [n] that expects
    [s] to evaluate to [Int i]. *)
let make_i n i s =
  [n >:: (fun _ -> assert_equal (Int i) (interp_small s));
   n >:: (fun _ -> assert_equal (Int i) (interp_big s))]

(** [make_b n b s] makes an OUnit test named [n] that expects
    [s] to evaluate to [Bool b]. *)
let make_b n b s =
  [n >:: (fun _ -> assert_equal (Bool b) (interp_small s));
   n >:: (fun _ -> assert_equal (Bool b) (interp_big s))]

(** [make_t n s] makes an OUnit test named [n] that expects
    [s] to fail type checking with error string [s']. *)
let make_t n s' s =
  [n >:: (fun _ -> assert_raises (Failure s') (fun () -> interp_small s));
   n >:: (fun _ -> assert_raises (Failure s') (fun () -> interp_big s))]
;;

let ex1 = "44 - 22"
let ex2 = "100 / 2"
let ex3 = "50 - 25 + 3 - 10 * 2"
let ex4 = "false / 9"
let ex5 = "30 - 15"
let ex6 = "64 / 0"
let ex7 = "90 - true"
let ex8 = "5 - 72 / 6"
let ex9 = "false - 20"
let ex10 = "56 / true"

let tests = [
  make_i "int" 22 "22";
  make_i "add" 22 "11+11";
  make_i "adds" 22 "(10+1)+(5+6)";
  make_i "sub" 0 "22 - 22";
  make_i "subs" 0 "(10 - 5) - (10 - 5)";
  make_i "sub1" 22 ex1;
  make_i "div1" 50 ex2;
  make_i "pemdas1" 8 ex3;
  make_i "sub2" 15 ex5;
  make_i "div2" (-7) ex8;
  make_i "let" 22 "let x=22 in x";
  make_i "lets" 22 "let x = 0 in let x = 22 in x";
  make_i "mul1" 22 "2*11";
  make_i "mul2" 22 "2+2*10";
  make_i "mul3" 14 "2*2+10";
  make_i "mul4" 40 "2*2*10";
  make_i "if1" 22 "if true then 22 else 0";
  make_b "true" true "true";
  make_b "leq" true "1<=1";
  make_i "if2" 22 "if 1+2 <= 3+4 then 22 else 0";
  make_i "if3" 22 "if 1+2 <= 3*4 then let x = 22 in x else 0";
  make_i "letif" 22 "let x = 1+2 <= 3*4 in if x then 22 else 0";
  make_t "ty div" bop_err ex4;
  make_t "div by zero" div_by_zero ex6;
  make_t "ty minus" bop_err ex7;
  make_t "ty minus2" bop_err ex9;
  make_t "ty div2" bop_err ex10;
  make_t "ty plus" bop_err "1 + true";
  make_t "ty mult" bop_err "1 * false";
  make_t "ty leq" bop_err "true <= 1";
  make_t "if guard" if_guard_err "if 1 then 2 else 3";
  make_t "if branch" if_branch_err "if true then 2 else false";
  make_t "unbound" unbound_var_err "x";
]
;;

let show_bop bop =
  match bop with
  | Add -> printf " + " 
  | Sub -> printf " - "
  | Mult -> printf " * " 
  | Div -> printf " / "
  | Leq -> printf " < "

let rec show_expr e =
  match e with
  | Var s -> printf "Var %s " s
  | Int i -> printf "Int %d " i
  | Bool b -> printf "Bool %B " b
  | Binop (bop, e1, e2)  -> printf "(Binop "; show_bop bop; show_expr e1; show_expr e2; printf ") "
  | Let (s, e1, e2) -> printf "(Let %s " s; show_expr e1; show_expr e2;  printf ") "
  | If (e1, e2, e3)  -> printf "(If "; show_expr e1; printf " Then "; show_expr e2; printf " Else "; show_expr e3;  printf ") "
;;

print_endline "\n";;
printf "Additional case 1: %B \n" ((Int 45 =  (interp_small "22+23")));;
printf "Additional case 2: %B \n" ((Int 45 =  (interp_small "22+24")));;
show_expr (interp_small "22+23");;
show_expr (interp_small "22+45");;
show_expr (interp_small "0+23");;
show_expr (interp_small "122+323");;
print_endline "";;
show_expr (interp_small "122+323+200");;
print_endline "";;

show_expr (parse "22+23");;
print_endline "";;

show_expr (parse "122+323+200");;
print_endline "";;

show_expr (parse "let x = 22 in x");;
print_endline "";;

show_expr (parse "let x = 0 in let x = 22 in x");;
print_endline "";;

show_expr (parse "if 1+2 <= 3*4 then let x = 22 in x else 0");;
print_endline "";;



print_endline "";;

let _ = run_test_tt_main ("suite" >::: List.flatten tests)
