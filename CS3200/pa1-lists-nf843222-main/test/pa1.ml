open Pa1__Lib
open Pa1__Util

(** [∀ l, l ++ [] = l] *)
let () = add_qcheck @@
           QCheck.(Test.make ~name:"append_right_identity" ~count:200
                     (small_list int)
                     (fun l -> append l [] = l))

(** [∀ a b c, (a ++ b) ++ c = a ++ (b ++ c)] *)
let () = add_qcheck @@
           QCheck.(Test.make ~name:"append_assoc" ~count:800
                     (triple (small_list int) (small_list int) (small_list int))
                     (fun (a, b, c) -> append (append a b) c = append a (append b c)))

(** [∀ a b, len (a ++ b) = len a + len b] *)
let () = add_qcheck @@
           QCheck.(Test.make ~name:"append_len" ~count:400
                     (pair (small_list int) (small_list int))
                     (fun (a, b) -> len (append a b) = len a + len b))

(** [∀ a l, snoc a l = l ++ [a]] *)
let () = add_qcheck @@
           QCheck.(Test.make ~name:"snoc_append" ~count:200
                     (pair (int) (small_list int))
                     (fun (a, l) -> snoc a l = append l [a]))

(** [∀ l, rev (rev l) = l] *)
let () = add_qcheck @@
           QCheck.(Test.make ~name:"rev_involutive" ~count:200
                     (small_list int) (fun l -> rev (rev l) = l))

(** [∀ l, len (rev l) = len l] *)
let () = add_qcheck @@
           QCheck.(Test.make ~name:"rev_len" ~count:200
                     (small_list int) (fun l -> len (rev l) = len l))

(** [∀ a b, rev (a ++ b) = rev b ++ rev a] *)
let () = add_qcheck @@
           QCheck.(Test.make ~name:"rev_append" ~count:400
                     (pair (small_list int) (small_list int))
                     (fun (a, b) -> rev (append a b) = append (rev b) (rev a)))

(** [∀ ls, len (flatten ls) = Σ len l, where l ∈ ls] *)
let () = add_qcheck @@
           QCheck.(Test.make ~name:"len_flatten" ~count:200
                     (small_list (small_list int))
                     (fun ls -> len (flatten ls) = List.fold_left (+) 0 (List.map len ls)))

(** [∀ l, len (isort l) = len l] *)
let () = add_qcheck @@
           QCheck.(Test.make ~name:"isort_len" ~count:200
                     (small_list int)
                     (fun l -> len (isort l) = len l))

(** A decider for whether a list of integers is sorted or not. *)
let rec is_sorted (l : int list) : bool =
  match l with
  | [] -> true
  | x :: xs ->
     match xs with
     | [] -> true
     | y :: _ -> x <= y && is_sorted xs

(** [∀ l, is_sorted (isort l)] *)
let () = add_qcheck @@
           QCheck.(Test.make ~name:"isort_is_sorted" ~count:200
                     (small_list int)
                     (fun l -> is_sorted (isort l)))

(** Remove a single occurrence of element [x] from list [l]. *)
let rec remove (x : 'a) (l : 'a list) : 'a list =
  match l with
  | [] -> []
  | y :: ys -> if x = y then ys else y :: remove x ys

(** [list_le a b = true] when every element in a has a matching element in b. *)
let rec list_le (l1 : 'a list) (l2 : 'a list) : bool =
  match l1 with
  | [] -> true
  | x :: xs -> List.mem x l2 && list_le xs (remove x l2)

(** List equivalence (permutation) is the symmetric closure of [list_le]. *)
let list_equiv (l1 : 'a list) (l2 : 'a list) : bool =
  list_le l1 l2 && list_le l2 l1

(** [∀ l, isort l ≃ l] *)
let () = add_qcheck @@
           QCheck.(Test.make ~name:"isort_equiv" ~count:200
                     (small_list int)
                     (fun l -> list_equiv (isort l) l))

(** Run the tests. *)
let () = Alcotest.run "PA1" [ ("test", !tests); ("qcheck", !qcheck_tests) ]
