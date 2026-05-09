type tree =
  | Leaf
  | Node of int * tree * tree
             
let rec size = function
  | Leaf -> 0
  | Node (_, l, r) -> Random.int(100) + size l + size r
;;

size Leaf;;
size (Node (1, Leaf, Leaf));;


let rec generate_tree (n: int) =
  if n = 0 then
    Leaf
  else if n = 1 then
    Node (Random.int(100), Leaf, Leaf)
  else
    let left_size = Random.int (n-1) + 1 in
    let right_size = n - left_size - 1 in
    Node (Random.int(100), generate_tree left_size, generate_tree right_size)


;;
size (generate_tree 5);;

size (generate_tree 11);;

size (generate_tree 10000);;

(* size(generate_tree 10000000);; *)

let rec height = function
  | Leaf -> 0
  | Node (_, l, r) -> max ((height l)+1)  ((height r)+1)
;;

generate_tree 5;;

height (generate_tree 5);;

height (generate_tree 100);;

height (generate_tree 10000000);;

let combine (v, left, right) = Node (v, left, right)
;;

combine (Random.int(100), Leaf, Leaf)
;;

(10, Leaf, Leaf) |> combine;;

(10, (generate_tree 3), (generate_tree 4)) |> combine |> size;;

(10, (generate_tree 3), (generate_tree 4)) |> combine |> size;;

( Random.int(100),
  (20, (generate_tree 3), (generate_tree 4)) |> combine,
  (30, (generate_tree 2), (generate_tree 3)) |> combine
) |> combine |> size
