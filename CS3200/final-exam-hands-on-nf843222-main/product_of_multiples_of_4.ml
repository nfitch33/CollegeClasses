open Printf


(* 
To compile, use:
  ocamlfind ocamlc -o product_of_multiples_of_4 -package oUnit -package num -linkpkg -g product_of_multiples_of_4.ml
*)

let _ = printf "\n+++++++++++++++++++++++++++++ The Product of Multiples of Four Problem +++++++++++++++++++++++++++++ \n";;

(****************************************************

Given a list of numbers, return the product of all elements of the list that are multiples of 4. If no multiples of 4 exist, return 1.

[1; 2; 10; 8; 9] -> 8
[2; 5; 4; 12; 8; 16] -> 6144
[5; 3; 9; 7]) -> 1
[] -> 1
[2] -> 1
[8; 10] -> 8
[5,0,9,] -> 0

****************************************************)
let passed_count = ref 0
let failed_count = ref 0

let rec product_of_multiples_of_4 lst =
  match lst with
  | [] -> 1
  | h :: t -> 
    if h mod 4 = 0 
      then h * product_of_multiples_of_4 t 
  else product_of_multiples_of_4 t



let pretty name expected actual =
  try
    if expected = actual then (
      incr passed_count;
      Printf.printf "%s : PASS\n" name
    ) else (
      incr failed_count;
      Printf.printf "%s : FAIL\n" name
    )
  with _ ->
    incr failed_count;
    Printf.printf "%s : FAIL\n" name
;;


let tests =
  [

    ("should return 6144 for list [2;5;4;12;8;16]",
     (6144, product_of_multiples_of_4 [2;5;4;12;8;16])
    );

    ("should return 1 for list [5;3;9;7]",
     (1, product_of_multiples_of_4 [5;3;9;7])
    );

    ("should return 442368 for list [24;16;32;36;7;89;5]",
     (442368, product_of_multiples_of_4 [24;16;32;36;7;89;5])
    );

    ("should return 0 for list [3;7;9;99;0]",
     (0, product_of_multiples_of_4 [3;7;9;99;0])
    );

    ("should return 20480 for list [4;6;8;40;7;16;9;81;41]",
     (20480, product_of_multiples_of_4 [4;6;8;40;7;16;9;81;41])
    );

  ]
;;


let _ =
  List.iter (fun (name, (expected, actual)) -> pretty name expected actual) tests;

  Printf.printf "\n==================== SUMMARY ====================\n";
  Printf.printf "PASSED: %d\n" !passed_count;
  Printf.printf "FAILED: %d\n" !failed_count;
  Printf.printf "=================================================\n";
  ()