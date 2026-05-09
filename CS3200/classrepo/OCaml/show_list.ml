(* This is an example showing the usage of the auxillary debugging function `show_list` *)

open Printf
open List
;;

let show_number n = 
  printf "sum_so_far = %d\n" n;
  n
in

let show_list lst = 
  iter (printf "%d ") lst; 
  printf "\n";
  lst 
in (* run `flush_all();;` afterwards to print out cache content in Jupyter notebook. *)

(* This is a tail-recursive version of summing a list *)

let rec sum_acc_show list sum_so_far: int =
    match list with
    | [] -> sum_so_far
    | h :: list' -> sum_acc_show (show_list list') (show_number (h + sum_so_far))
in
  
let sumT_show list = sum_acc_show list 0  in

let rec sum_acc list sum_so_far: int =
  match list with
  | [] -> sum_so_far
  | h :: list' -> sum_acc list' (h + sum_so_far)
in

let sumT list = sum_acc list 0  in

let s = sumT_show (show_list [1;2;3;4;5;6;7;8;9;10]) in
  printf "sum_show = %d\n\n" s ;
  [1;2;3;4;5;6;7;8;9;10] |> show_list |> sumT |> printf "sum = %d\n"