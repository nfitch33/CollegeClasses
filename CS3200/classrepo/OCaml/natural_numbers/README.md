```ocaml
type nat = Zero | Succ of nat
             
let zero = Zero
let one = Succ zero
let two = Succ one
let three = Succ two
let four = Succ three
    
let iszero = function
  | Zero -> true
  | Succ _ -> false

let pred = function
  | Zero -> failwith "pred Zero is undefined"
  | Succ m -> m    
    
let rec add n1 n2 =
  match n1 with
  | Zero -> n2
  | Succ pred_n -> add pred_n (Succ n2)
                     
let rec int_of_nat = function
  | Zero -> 0
  | Succ m -> 1 + int_of_nat m

let rec nat_of_int = function
  | i when i = 0 -> Zero
  | i when i > 0 -> Succ (nat_of_int (i - 1))
  | _ -> failwith "nat_of_int is undefined on negative ints" 
;;           
           
nat_of_int 0;;           
nat_of_int 1;;           
nat_of_int 2;;
add two three;;
int_of_nat three;;
int_of_nat (add two three);;

```

[Try it](https://try.ocamlpro.com/#code/(*'This'is'an'OCaml'editor.!'''Enter'your'program'here'and'send'it'to'the'toplevel'using'the'$(Eval'code$(!button'or'$/Ctrl-e$1.'*)!!type'nat'='Zero'$5'Succ'of'nat!!let'zero'='Zero!let'one'='Succ'zero!let'two'='Succ'one!let'three'='Succ'two!let'four'='Succ'three!!let'iszero'='function!$5'Zero'-$.'true!$5'Succ'_'-$.'false!!let'pred'='function!$5'Zero'-$.'failwith'$(pred'Zero'is'undefined$(!$5'Succ'm'-$.'m!!let'rec'add'n1'n2'=!match'n1'with!$5'Zero'-$.'n2!$5'Succ'pred_n'-$.'add'pred_n'(Succ'n2)!!let'rec'int_of_nat'='function!$5'Zero'-$.'0!$5'Succ'm'-$.'1'+'int_of_nat'm!!let'rec'nat_of_int'='function!$5'i'when'i'='0'-$.'Zero!$5'i'when'i'$.'0'-$.'Succ'(nat_of_int'(i'-'1))!$5'_'-$.'failwith'$(nat_of_int'is'undefined'on'negative'ints$(!;;!!nat_of_int'0;;!nat_of_int'1;;!nat_of_int'2;;!add'two'three;;!int_of_nat'three;;!int_of_nat'(add'two'three);;)
