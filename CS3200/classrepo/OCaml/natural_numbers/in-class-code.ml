type nat = Zero | Succ of nat
             
let zero = Zero
let one = Succ zero
let two = Succ one
let three = Succ two
let four = Succ three
let five = Succ four
    
    
let iszero = function
  | Zero -> true
  | Succ _ -> false

let pred = function  (* n - 1 *)
  | Zero -> failwith "pred Zero is undefined"
  | Succ m -> m
;;

let rec add n1 n2 =
  match n1 with
  | Zero -> n2
  | Succ pred_n -> add pred_n (Succ n2)
;;

pred (pred (pred three));;

add one two;;

add two three;;

add three zero;;


let rec sub n1 n2 = (* n1 - n2 *) (* sub 5 3 = 2 *)
  match n2 with
  | Zero -> n1
  | Succ Zero -> pred n1
  | Succ pred_n -> pred (sub n1 pred_n)  (* pred_n = 1 *)
                     
                     
let rec int_of_nat = function
  | Zero -> 0
  | Succ m -> 1 + int_of_nat m

let rec nat_of_int = function
  | i when i = 0 -> Zero
  | i when i > 0 -> Succ (nat_of_int (i - 1))
  | _ -> failwith "nat_of_int is undefined on negative ints"

;;

int_of_nat one;;

int_of_nat four;;

int_of_nat five;;

int_of_nat (pred five);;

nat_of_int 5;;

nat_of_int 0;;
