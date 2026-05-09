(* rbt: Red Black Tree *)

open QCheck

open Set

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

let rec rbt_forall (pred : 'a -> bool) (t : 'a rbtree) : bool =
  match t with
  | RBLeaf -> true
  | RBNode (_, x, l, r) -> pred x && rbt_forall pred l && rbt_forall pred r

let root_black (t : 'a rbtree) : bool =
  color_of t = Black

let rec red_children_black (t : 'a rbtree) : bool =
  match t with
  | RBLeaf -> true
  | RBNode (c, _, l, r) ->
      red_children_black l && red_children_black r &&
      (c = Black || (color_of l = Black && color_of r = Black))

let rec rbt_bst_inv (lt : 'a -> 'a -> bool) (t : 'a rbtree) : bool =
  match t with
  | RBLeaf -> true
  | RBNode (_, x, l, r) -> rbt_forall (fun y -> lt y x) l &&
                             rbt_forall (lt x) r &&
                               rbt_bst_inv lt l && rbt_bst_inv lt r

let paths_well_formed (t : 'a rbtree) : bool =
  let rec go (t' : 'a rbtree) : int option =
    match t' with
    | RBLeaf -> Some 1
    | RBNode (c, _, l, r) ->
       match (go l, go r) with
       | (None, _) -> None
       | (_, None) -> None
       | (Some n, Some m) ->
          if n = m then Some (n + if c = Black then 1 else 0) else None
  in
  match go t with
  | None -> false
  | Some _ -> true

let rbt_inv (le : 'a -> 'a -> bool) (t : 'a rbtree) : bool =
  root_black t
  && red_children_black t
  && paths_well_formed t
  && rbt_bst_inv (fun x y -> le x y && not (le y x)) t

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

    (** 9. (1 pts) Write a 'union' function for taking the union of
       two RBTs. Hint: similar to #6. *)
    let rec union a b =
      match a with
      | RBLeaf -> b
      | RBNode (_, x, l, r) -> insert x (union l (union r b))
                             
    (** 10. (1 pts) Write an 'intersection' function for taking the
       intersection of two RBTs. Hint: similar to #7. *)
    let rec intersection a b =
      match a with
      | RBLeaf -> RBLeaf
      | RBNode (c, x, l, r) ->
         if elem x b then
           RBNode (c, x, intersection l b, intersection r b)
         else
           union (intersection l b) (intersection r b)

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
