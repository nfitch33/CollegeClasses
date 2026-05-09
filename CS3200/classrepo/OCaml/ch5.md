## Ch5.9 Functor

"A functor is simply a 'function' from modules to modules."

"Functor types are an example of an advanced programming language feature called **dependent types**, with which the type of an output is determined by the value of an input. That’s different than the normal case of a function, where it’s the output value that’s determined by the input value, and the output type is independent of the input value."

```ocaml
module F (M : sig val x : int end) = struct let y = M.x end
module X = struct let x = 0 end
module Z = struct let x = 0;; let z = 0 end
module T = struct let t = 0;; let z = 0 end
module FX = F (X)
module FZ = F (Z)
module FT = F (T)
```
```
module F : functor (M : sig val x : int end) -> sig val y : int end
module X : sig val x : int end
module Z : sig val x : int val z : int end
module FX : sig val y : int end
module FZ : sig val y : int end
```
