```ocaml
exception DivisionByZero

let divide x y =
  if y = 0 then
    raise DivisionByZero
  else
    x / y

let () =
  try
    let result = divide 10 0 in
    print_int result
  with
  | DivisionByZero ->
      print_endline "Here's an Error: Division by zero"
        
        
;;
let divide x y =
  if y = 0 then
    None
  else
    Some (x / y)

let () =
  match divide 10 0 with
  | None -> print_endline "Here's the same Error: Division by zero"
  | Some result -> print_int result
;;

```
