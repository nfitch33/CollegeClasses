# OCaml type system example:

The following code works because of the localized, hierarchical nature of the type system

```ocaml
let f x = 2 in
    (f 3) + (f 3.0)
```

The same code won't work if it's in the body of function `f`

```ocaml
let rec f x = 
  if (Random.int 100 > 50) then
    f 2
  else
    f 3.0
;;

(f 2) + (f 3.0)
```
