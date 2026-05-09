## Ch8.8 Monads

```ocaml
let ( + ) (x : int option) (y : int option) : int option =
  x >>= fun a ->
    y >>= fun b ->
      return (Stdlib.( + ) a b)
```
