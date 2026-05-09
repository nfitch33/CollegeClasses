(************************************************************************
0. Fill your name and OU ID or PID on the line below:
 *)
let name ="Nathaniel Fitch";;
let id = "P101093645";;
let _ = Printf.printf "\n-----NAME: %s ID:%s -----\n" name id;;

open QCheck
open Alcotest

open Set
open Util

(** [Sets]

   In this assignment you will develop a collection of Set modules
   that can be used for working with sets in future assignments. The
   file 'set.ml' contains the Set interface. Take a look at it now. It
   specifies the operations that every Set module must define. The Set
   interface is given as a module type (or "signature"). See section
   5.2 of the book to learn about modules and module types:
   https://cs3110.github.io/textbook/chapters/modules/modules.html.

   The file '/test/pa3.ml' contains a test module for sets. The test
   module is instantiated with three different implementations: one
   based on lists, one based on binary search trees, and one based on
   balanced binary search trees. All three are defined in the current
   file below, but they are incomplete. It's your job to fill in the
   missing pieces.  *)

(** Part 1 (List sets)

   The first implementation of the Set signature uses lists to store
   the elements. We enforce a simple invariant: lists that represent
   sets do not contain any duplicate elements. *)

(* A checker for the SetList invariant. Evaluates to true iff the
   given list contains no duplicates. *)
let rec nodup (l : 'a list) : bool =
  match l with
  | [] -> true
  | x :: xs -> List.for_all (fun y -> x <> y) xs && nodup xs

(** 1. (10 pts) Write a function 'dedup' that removes duplicate
   elements from a list. That is, the output should be a list
   containing all the same elements as the input except for
   duplicates. Hint: structural recursion and List.filter. *)

let rec dedup (l : 'a list) : 'a list =
  match l with
  | [] -> []
  | x :: xs ->
      let xs' = dedup xs in
      if List.mem x xs' then xs' else x :: xs'

let () = add_test "dedup" @@
           fun _ ->
           (check @@ list int) "" [] (dedup []);
           (check @@ list int) "" [1] (dedup [1]);
           (check @@ list int) "" [1] (dedup [1; 1]);
           (check @@ list int) "" [1; 2; 3] (dedup [1; 2; 3]);
           (check @@ list int) "" [1; 2; 3] (dedup [1; 2; 1; 3]);
           (check @@ list int) "" [1; 2; 3] (dedup [1; 2; 2; 1; 3]);
           (check @@ list char) "" ['m'; 'o'] (dedup ['m'; 'o'; 'o'])

(* [∀ l, nodup (dedup l))] *)
let () = add_qcheck @@
           QCheck.Test.make ~name:"nodup_dedup" ~count:100
             (small_list small_int)
             (fun l -> nodup (dedup l))

(* [∀ l, l ⊆ dedup l] *)
let () = add_qcheck @@
           QCheck.Test.make ~name:"dedup_sound" ~count:100
             (small_list small_int)
             (fun l -> let l' = dedup l in
                       List.for_all (fun x -> List.mem x l') l)

(* List-backed sets. *)
module ListSet : functor (T : Type) ->
                 Set with type elt = T.t with type t = T.t list =
  functor
    (T : Type) -> struct
    type elt = T.t
    type t = T.t list

    (* QCheck generator for lists with no duplicates. *)
    let gen = QCheck.make (Gen.map dedup (Gen.small_list T.gen.gen))

    (* Render list to string. *)
    let show l = string_of_list T.show l

    (* The empty set is represented by the empty list. *)
    let empty = []

    (* A singleton set is represented by a list containing a single element. *)
    let single x = [x]

    (** 2. (10 pts) Write the 'insert' function for ListSets. Remember
       to preserve the ListSet invariant: no duplicates! Hint:
       'List.mem' could be useful. https://v2.ocaml.org/api/List.html *)
    let insert (x : elt) (l : elt list) : elt list =
      if List.mem x l then l else x :: l

   (** 3. (10 pts) Write the 'elem' function for ListSets. *)
    let rec elem (x : elt) (l : elt list) : bool =
      match l with
      | [] -> false
      | y :: ys -> x = y || elem x ys

    (** 4. (10 pts) Write the 'union' function for ListSets. Hint:
       'insert' could be useful. *)
    let rec union (a : elt list) (b : elt list) : elt list =
      match a with
      | [] -> b
      | x :: xs -> insert x (union xs b)

    (** 5. (10 pts) Write the 'intersection' function for
       ListSets. Hint: 'List.filter' could be useful. *)
    let intersection (a : elt list) (b : elt list) : elt list =
      List.filter (fun x -> List.mem x b) a

    (* Use dedup to establish the ListSet invariant. *)
    let of_list = dedup

    (* Trivial since already a list. *)
    let to_list l = l

    (* a ⊆ b iff ∀ x, x ∈ a → x ∈ b *)
    let subset a b = List.for_all (fun x -> List.mem x b) a

    (* First check that lengths are equal to avoid the more expensive
       subset operations when the lists are obviously not
       equal. Otherwise, compute the symmetric closure of the subset relation. *)
    let eq a b = List.length a = List.length b && subset a b && subset b a

    let inv = nodup
  end


(** Part 2 (BST sets)

   Now you will implement the set interface using the following
   datatype, 'a bst, which defines polymorphic binary search trees
   parameterized by the type 'a of data contained at the leaves.  *)

type 'a bst =
  | Leaf
  | Node of 'a * 'a bst * 'a bst

(* Curried form of node constructor for convenience. *)
let node x l r = Node (x, l, r)

(* Render bst to string. *)
let rec string_of_bst (show : 'a -> string) : 'a bst -> string = function
  | Leaf -> "Leaf"
  | Node (x, l, r) -> "Node (" ^ show x ^ ", " ^
                        string_of_bst show l ^ ", " ^
                          string_of_bst show r ^ ")"

(* Testing voodoo. *)
let bst (show : 'a -> string) : ('a bst) testable =
  let pp_btree ppf t = Fmt.pf ppf "%s" (string_of_bst show t) in
  testable pp_btree ( = )

(** For BSTs we enforce an even stronger invariant: BSTs contain no
   duplicates, and are in sorted order.

   That is:
     for any [Node (x, l, r)], we have
       y < x for all y ∈ l, and
       x < z for all z ∈ r.

   In English: At every node, all elements appearing in the left
   subtree are *less than* the current node's element, and all
   elements appearing in the right subtree are *greater than* the
   current node's element. *)

(* Check that a given predicate holds on all elements in a BST. *)
let rec bst_forall (pred : 'a -> bool) (t : 'a bst) : bool =
  match t with
  | Leaf -> true
  | Node (x, l, r) -> pred x && bst_forall pred l && bst_forall pred r

(* Check the BST invariant. *)
let rec bst_inv (lt : 'a -> 'a -> bool) (t : 'a bst) : bool =
  match t with
  | Leaf -> true
  | Node (x, l, r) -> bst_forall (fun y -> lt y x) l &&
                        bst_forall (lt x) r &&
                          bst_inv lt l && bst_inv lt r

module BstSet : functor (Ord : OType) ->
                Set with type elt = Ord.t with type t = Ord.t bst =
  functor
    (Ord : OType) -> struct
    type elt = Ord.t
    type t = Ord.t bst

    (* Render a BST to string. *)
    let show t = string_of_bst Ord.show t

    (* The empty set is a represented by a leaf. *)
    let empty = Leaf

    (* A singleton set is represented by a node with two leaf children. *)
    let single x = Node (x, Leaf, Leaf)

    (* Check for membership of an element in a BST. Exploits the BST
       invariant for efficiency. *)  
    let rec elem x = function
      | Leaf -> false
      | Node (y, l, r) ->
         x = y || elem x (if Ord.le x y then l else r)

    (** 6. (10 pts) Write an 'insert' function for inserting a single
       element into a BST. Make sure to preserve the BST invariant! *)
    let rec insert x t =
      match t with
      | Leaf -> Node (x, Leaf, Leaf)
      | Node (y, l, r) ->
         if x = y then t
         else if Ord.le x y then Node (y, insert x l, r)
         else Node (y, l, insert x r)

    (** 7. (10 pts) Write a 'union' function for taking the union of
       two BSTs. Hint: structural recursion and 'insert'. *)
    let rec union (a : elt bst) (b : elt bst) : elt bst =
      match a with
      | Leaf -> b
      | Node (x, l, r) ->
         let b_with_x = insert x b in
         let b_with_l = union l b_with_x in
         union r b_with_l

    (** 8. (10 pts) Write an 'intersection' function for taking the
       intersection of two BSTs. Hint: you may find it useful to use
       'union' from above. *)
    let rec intersection (a : elt bst) (b : elt bst) : elt bst =
      match a with
      | Leaf -> Leaf
      | Node (x, l, r) ->
         let l' = intersection l b in
         let r' = intersection r b in
         if elem x b then insert x (union l' r') else union l' r'

    (* Convert a list to a BST. *)
    let rec of_list = function
      | [] -> Leaf
      | x :: xs -> insert x (of_list xs)

    (* Convert a BST to a list *)
    let rec to_list = function
      | Leaf -> []
      | Node (x, l, r) -> x :: to_list l @ to_list r

    let subset a b = bst_forall (fun x -> elem x b) a                

    let eq a b = subset a b && subset b a

    let bst_gen : ('a bst) Gen.t =
      Gen.map of_list (Gen.small_list Ord.gen.gen)

    let gen : ('a bst) arbitrary =
      let open QCheck.Iter in
      let rec shrink_bst = function
        | Leaf -> empty
        | Node (x, l, r) ->
           of_list [l; r]
           <+> (shrink_bst l >|= fun l' -> node x l' r)
           <+> (shrink_bst r >|= fun r' -> node x l r')
      in
      QCheck.make bst_gen ~print:(string_of_bst Ord.show) ~shrink:shrink_bst

    let inv = bst_inv Ord.le
  end



(** Part 3 (Red-black tree sets)

   The following data structure, RBTree, defines red-black binary
   trees (essentially just BTrees augmented with color information --
   red or black). If you haven't seen such trees before, or just
   forget, you can refresh your memory by reading the article here:
   https://en.wikipedia.org/wiki/Red%E2%80%93black_tree. *)

type color =
  | Red
  | Black

type 'a rbtree =
  | RBLeaf
  | RBNode of (color * 'a * 'a rbtree * 'a rbtree)

let color_of (t : 'a rbtree) : color =
  match t with
  | RBLeaf -> Black
  | RBNode (c, _, _, _) -> c

let string_of_color = function
  | Red -> "Red"
  | Black -> "Black"

let rec string_of_rbt (show : 'a -> string) : 'a rbtree -> string = function
  | RBLeaf -> "RBLeaf"
  | RBNode (c, x, l, r) ->
     "RBNode (" ^ string_of_color c ^ ", " ^ show x ^ ", " ^
       string_of_rbt show l ^ ", " ^ string_of_rbt show r ^ ")"

(* Curried constructors for convenience. *)
let leaf : 'a rbtree = RBLeaf
let node c x l r = RBNode (c, x, l, r)

(* Some rbtrees for testing: *)
let r1 = node Black 2 (node Red 1 leaf leaf) (node Red 3 leaf leaf)
let r2 = node Red 1 leaf leaf
let r3 = node Black 4
           (node Red 2
              (node Black 1 leaf leaf)
              (node Red 3 leaf leaf))
           (node Red 6
              (node Black 5 leaf leaf)
              (node Black 7 leaf leaf))
let r4 = node Black 4
           (node Red 2
              (node Black 1 leaf leaf)
              (node Black 3 leaf leaf))
           (node Black 6 leaf leaf)
let r5 = node Black 4
           (node Red 2
              (node Black 1 leaf leaf)
              (node Black 3 leaf leaf))
           (node Red 6
              (node Red 5 leaf leaf)
              (node Black 7 leaf leaf))
let r6 = node Black 4
           (node Red 2
              (node Black 1 leaf leaf)
              (node Black 3 leaf leaf))
           (node Red 8
              (node Black 6 leaf leaf)
              (node Black 10 leaf leaf))
let r7 = node Black 4
           (node Red 2
              (node Black 1 leaf leaf)
              (node Black 3 leaf leaf))
           (node Black 6
              (node Black 5 leaf leaf)
              (node Black 7 leaf leaf))
let r8 = node Black 1
           (node Red 3 leaf leaf)
           (node Red 2 leaf leaf)
(* END RBTrees used for testing *)

(** In order for an RBTree to be a valid red-black tree, all of the
   following properties must hold:

   (o) All nodes are either red or black.

   (i) The root node is black.

   (ii) All leaves are black.

   (iii) If a node is red, then both its children are black.

   (iv) Any path from any node in the tree to any of its descendent
   black leaf nodes has the same number of black nodes (not including
   the node itself but including the leaf node) as any other such path
   from that node.

   (v) The tree additionally satisfies the binary search tree
   invariant. These properties together imply that the height of an
   RBTree is pretty much balanced -- no left subtree of a node can be
   more than 2x deeper than the right subtree of that node, and vice
   versa. *)

(** 9. (10 pts) Define a function 'rbt_inv' that determines whether a
   given RBTree satisfies the RBT invariant as described above.

   HINT 1: You probably don't need to directly encode properties (o)
   and (ii) -- they are automatically true of every RBTree by
   construction.

   HINT 2: You may find it helpful to define one function for each
   property (i--iv) above. Then your overall rbt_inv function can just
   string these individual invariant-checking functions together. *)

(* Check that a given predicate holds on all elements in a BST. *)
let rec rbt_forall (pred : 'a -> bool) (t : 'a rbtree) : bool =
  match t with
  | RBLeaf -> true
  | RBNode (_, x, l, r) -> pred x && rbt_forall pred l && rbt_forall pred r

let rec is_bst (le : 'a -> 'a -> bool) (t : 'a rbtree) : bool =
  let rec max_in = function
    | RBLeaf -> None
    | RBNode (_, x, _, r) ->
       match max_in r with None -> Some x | s -> s
  in
  let rec min_in = function
    | RBLeaf -> None
    | RBNode (_, x, l, _) ->
       match min_in l with None -> Some x | s -> s
  in
  match t with
  | RBLeaf -> true
  | RBNode (_, x, l, r) ->
     let ok_left =
       match max_in l with
       | None -> true
       | Some m -> le m x
     in
     let ok_right =
       match min_in r with
       | None -> true
       | Some m -> le x m
     in
     ok_left && ok_right && is_bst le l && is_bst le r

let rec black_height (t : 'a rbtree) : int option =
  match t with
  | RBLeaf -> Some 1
  | RBNode (c, _, l, r) ->
     (match (black_height l, black_height r) with
      | (Some hl, Some hr) when hl = hr ->
         let valid =
           match c, l, r with
           | Red, RBNode (Red, _, _, _), _
           | Red, _, RBNode (Red, _, _, _) -> false
           | _ -> true
         in
         if not valid then None
         else Some (hl + if c = Black then 1 else 0)
      | _ -> None)

let rbt_inv (le : 'a -> 'a -> bool) (t : 'a rbtree) : bool =
  let root_black =
    match t with
    | RBLeaf -> true
    | RBNode (c, _, _, _) -> c = Black
  in
  root_black && is_bst le t && Option.is_some (black_height t)

let () = add_test "rbt_inv" @@
           fun _ ->
           (check Alcotest.bool) "r1 satisfies rbt_inv" true (rbt_inv (<=) r1);
           (check Alcotest.bool) "r2 violates rbt_inv" false (rbt_inv (<=) r2);
           (check Alcotest.bool) "r3 violates rbt_inv" false (rbt_inv (<=) r3);
           (check Alcotest.bool) "r4 satisfies rbt_inv" true (rbt_inv (<=) r4);
           (check Alcotest.bool) "r5 violates rbt_inv" false (rbt_inv (<=) r5);
           (check Alcotest.bool) "r6 satisfies rbt_inv" true (rbt_inv (<=) r6);
           (check Alcotest.bool) "r7 violates rbt_inv" false (rbt_inv (<=) r7);
           (check Alcotest.bool) "r8 violates rbt_inv" false (rbt_inv (<=) r8)

module RbtSet : functor (Ord : OType) ->
                Set with type elt = Ord.t with type t = Ord.t rbtree =
  functor (Ord : OType) -> struct
    type elt = Ord.t
    type t = Ord.t rbtree

    let empty = leaf

    let single x = node Red x leaf leaf

    (* Check for membership of an element in an RBT. Exploits the
       BST invariant for efficiency. *)  
    let rec elem x t =
      match t with
      | RBLeaf -> false
      | RBNode (_, y, l, r) ->
         x = y || if Ord.le x y then elem x l else elem x r

    (* https://www.cs.tufts.edu/comp/150FP/archive/chris-okasaki/redblack99.pdf *)        
    let balance (c : color) (z : 'a) (l : 'a rbtree) (r : 'a rbtree) : 'a rbtree =
      match (c, l, r) with
      | (Black, RBNode (Red, y, RBNode (Red, x, a, b), c), d) ->
         node Red y (node Black x a b) (node Black z c d)
      | (Black, RBNode (Red, x, a, RBNode (Red, y, b, c)), d) ->
         node Red y (node Black x a b) (node Black z c d)
      | (Black, a, RBNode (Red, x, RBNode (Red, y, b, c), d)) ->
         node Red y (node Black z a b) (node Black x c d)
      | (Black, a, RBNode (Red, y, b, RBNode (Red, x, c, d))) ->
         node Red y (node Black z a b) (node Black x c d)
      | _ -> node c z l r

    (* Insert an element in an RBT while preserving rbt_inv. *)
    let insert (x : 'a) (t : 'a rbtree) : 'a rbtree =
      let make_black (b : 'a rbtree) : 'a rbtree =
        match b with
        | RBLeaf -> RBLeaf
        | RBNode (_, y, l, r) -> RBNode(Black, y, l, r)
      in
      let rec ins (b : 'a rbtree) : 'a rbtree =
        match b with
        | RBLeaf -> node Red x leaf leaf
        | RBNode (c, y, l, r) ->
           if x = y then node c y l r
           else if Ord.le x y then balance c y (ins l) r
           else balance c y l (ins r)
      in
      make_black (ins t)

    (** 10. (5 pts) Write a 'union' function for taking the union of
       two RBTs. Hint: similar to #6. *)
    let rec union (a : elt rbtree) (b : elt rbtree) : elt rbtree =
      match a with
      | RBLeaf -> b
      | RBNode (_, x, l, r) -> insert x (union l (union r b))

    (** 11. (5 pts) Write an 'intersection' function for taking the
       intersection of two RBTs. Hint: similar to #7. *)
    let rec intersection (a : elt rbtree) (b : elt rbtree) : elt rbtree =
      match a with
      | RBLeaf -> leaf
      | RBNode (_, x, l, r) ->
         let l' = intersection l b in
         let r' = intersection r b in
         if elem x b then insert x (union l' r') else union l' r'

    let rec of_list l =
      match l with
      | [] -> leaf
      | x :: xs -> insert x (of_list xs)

    let rec to_list t =
      match t with
      | RBLeaf -> []
      | RBNode (_, x, l, r) -> x :: to_list l @ to_list r

    let subset a b = rbt_forall (fun x -> elem x b) a

    let eq a b = subset a b && subset b a

    let gen = QCheck.make (Gen.map of_list (Gen.small_list Ord.gen.gen))
                ~print:(string_of_rbt Ord.show)

    let show = string_of_rbt Ord.show

    let inv = rbt_inv Ord.le
  end

