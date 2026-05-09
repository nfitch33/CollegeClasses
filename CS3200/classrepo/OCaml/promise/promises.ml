(* To compile this file, use command:

ocamlfind ocamlc -o promises -package lwt -package lwt.unix -thread -linkpkg -g promises.ml

You may need to do this first:

opam install ocamlfind

*)


open Lwt
open Lwt_io

let (p : int Lwt.t), r = Lwt.wait ()
;;

let print_the_int int = Lwt_io.printf "The int is: %d\n" int
;;

Lwt.bind p print_the_int
;;

print_endline "Now resolve the promise.\n"
;;

Lwt.wakeup r 42
;; 

(* Watch the order of the printouts in the terminal. *)

(* 
@drchangliu ➜ /workspaces/examples/ocaml (main) $ ocamlfind ocamlc -o promises -package lwt -package lwt.unix -thread -linkpkg -g promises.ml
@drchangliu ➜ /workspaces/examples/ocaml (main) $ ./promises
Now resolve the promise.

The int is: 42
*)