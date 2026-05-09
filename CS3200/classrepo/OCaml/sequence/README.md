https://ocaml.org/manual/5.2/api/Seq.html

```ocaml
let take n seq =
  let rec aux n seq () =
    if n <= 0 then
      Seq.Nil
    else
      match seq () with
      | Seq.Nil -> Seq.Nil
      | Seq.Cons (x, rest) -> Seq.Cons (x, aux (n - 1) rest)
  in
  aux n seq

(* Define an infinite sequence of natural numbers starting from 1 *)
let rec from n () = Seq.Cons (n, from (n + 1))
let nats = from 1

(* Use the 'take' function to get the first 5 elements *)
let first_five = take 5 nats

(* Convert the sequence to a list to display the elements *)
let list_of_first_five = List.of_seq first_five
;;

(* Print the list *)
List.iter (fun x -> print_int x; print_string " ") list_of_first_five
;;

take 100 nats
;;

List.of_seq (take 10 nats)
;;
```
