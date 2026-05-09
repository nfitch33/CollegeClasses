(* To compile this file, use command:

ocamlfind ocamlc -o promises2 -package lwt -package lwt.unix -thread -linkpkg -g promises2.ml

*)


open Lwt
open Lwt_io

let (p1 : int Lwt.t), r1 = Lwt.wait ();;
let (p2 : int Lwt.t), r2 = Lwt.wait ();;
let (p3 : int Lwt.t), r3 = Lwt.wait ();;

let print_the_int int = Lwt_io.printf "The int is: %d\n" int;;
let print_the_int2 int = Lwt_io.printf "The int 2 IS: %d !!\n" int;;

print_endline "Now resolve the promises.";;

Lwt.wakeup r1 41;;

print_endline "Wake up p1 with 41.";;

Lwt.bind p1 print_the_int;;
print_endline "Bind p1 with the funtion.";;
Lwt.bind p2 print_the_int;;

Lwt.bind p2 print_the_int2;;

Lwt.bind p3 print_the_int;;

Lwt.wakeup r2 42;;
Lwt.wakeup_exn r2 (Failure "failure r2");;
print_endline "Waking up r3 with exception.";;
Lwt.wakeup_exn r3 (Failure "failure r3");; 
print_endline "Waking up r3 with 43.";;
Lwt.wakeup r3 43;;
(* Lwt.wakeup r1 44;; *)


(*
@drchangliu ➜ /workspaces/examples/ocaml (main) $ ocamlfind ocamlc -o promises2 -package lwt -package lwt.unix -thread -linkpkg -g promises2.ml
@drchangliu ➜ /workspaces/examples/ocaml (main) $ ./promises2
Now resolve the promises.
Wake up p1 with 41.
Bind p1 with the funtion.
The int is: 41
The int 2 IS: 42 !!
The int is: 42
Fatal error: exception Invalid_argument("Lwt.wakeup_exn")
@drchangliu ➜ /workspaces/examples/ocaml (main) $
*)