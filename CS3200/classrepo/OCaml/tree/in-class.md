```ocaml
type tree =
  | Leaf
  | Node of  tree * tree
             
let rec size = function
  | Leaf -> 0
  | Node (l, r) -> 1 + size l + size r
;;

size Leaf;;
size (Node (Leaf, Leaf));;


let rec generate_tree (n: int) =
  if n = 0 then
    Leaf
  else if n = 1 then
    Node (Leaf, Leaf)
  else
    let left_size = Random.int (n-1) + 1 in
    let right_size = n - left_size - 1 in
    Node (generate_tree left_size, generate_tree right_size)


;;
size (generate_tree 5);;

size (generate_tree 11);;

size (generate_tree 10000);;

(* size(generate_tree 10000000);; *)

let rec height = function
  | Leaf -> 0
  | Node (l, r) -> max ((height l)+1)  ((height r)+1)
;;

height (generate_tree 5);;

height (generate_tree 100);;

height (generate_tree 10000000);;
```

Output:
```ocaml
height (generate_tree 10000000) ;;
- : int = 56
```
## An attempt to implement a three-way operator (a T-shaped pipeline)

A `combine` function that takes two parameters
```ocaml
let combine left right = Node (left, right)
```

Another `combine` function that takes only one parameter, which is a tuple with two fields. 

```ocaml
let combine (left, right) = Node (left, right)
;;

combine (Leaf, Leaf)
;;

(Leaf, Leaf) |> combine;;

((generate_tree 3), (generate_tree 4)) |> combine |> size;;

((generate_tree 3), (generate_tree 4)) |> combine |> size;;

(
  ((generate_tree 3), (generate_tree 4)) |> combine,
  ((generate_tree 2), (generate_tree 3)) |> combine
) |> combine |> size
```
