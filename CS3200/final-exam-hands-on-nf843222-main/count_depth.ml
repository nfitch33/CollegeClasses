open Printf
open OUnit

let _ = printf "\n+++++++++++++++++++++++++++++ The Count Depth Tree Problem +++++++++++++++++++++++++++++ \n"

(****************************************************

Given a tree, return the depth of the tree.

This tree structure is a **general N-ary tree**: each Branch contains a 
*list* of children. A node may have 0, 1, 2, or many subtrees.

Visual Representation of This Tree Type
---------------------------------------

type tree =
  | Leaf of string
  | Branch of tree list

This means:
1. A Leaf has no children: depth = 1

2. A Branch can have ANY number of children: Branch [t1; t2; t3]

Visual form:

               Branch
            /     |     \
          t1     t2     t3


3. Depth is defined as the **maximum path from root to any leaf**.

Example Tree
------------------------------------
tree = Branch [Leaf "true"; Branch [Leaf "false"]]

                   Branch
                 /        \
        Leaf("t")        Branch
                           |
                        Leaf("f")
       depth = 3


Your task:
Implement count_depth so that it returns the correct depth for any
general tree structure.

Note that no test cases are provided here other than the trivial examples. 
You are asked to design a sufficient number of test cases with meaningful coverage. 
You are encouraged but not required to use OUnit.
****************************************************)

(* Define the tree data structure *)
type tree =
  | Leaf of string
  | Branch of tree list

(* Placeholder for unimplemented functionality *)
let ____todo____ (type t) (x : t) : 'a =
  let module M = struct exception Todo of t end in
  raise @@ M.Todo x

(* Recursive function to calculate the depth of the entire tree *)
let rec count_depth (t : tree) : int = 
  fold_tree (count_depth _ l r -> 1 + max l r) 0 t

;;
(* Example trees for testing *)
let tree1 = Leaf "true"  (* Depth: 1 *)
let tree2 = Branch [Leaf "true"; Leaf "false"]  (* Depth: 2 *)
let tree3 = Branch [Leaf "true"; Branch [Leaf "false"]]  (* Depth: 3 *)
let tree4 = Branch [Leaf "true"; Branch [Leaf "false"; Branch [Leaf "true"]]]  (* Depth: 4 *)
let tree5 = Branch [Branch [Leaf "a"; Leaf "b"]; Leaf "c"; Branch [Leaf "d"; Branch [Leaf "e"]]]  (* Depth: 4 *)

(* Print expected results *)
let () = printf "Expected: 1, Actual: %d\n" (try count_depth tree1 with _ -> -1)
let () = printf "Expected: 2, Actual: %d\n" (try count_depth tree2 with _ -> -1)
let () = printf "Expected: 3, Actual: %d\n" (try count_depth tree3 with _ -> -1)
let () = printf "Expected: 4, Actual: %d\n" (try count_depth tree4 with _ -> -1)
let () = printf "Expected: 4, Actual: %d\n" (try count_depth tree5 with _ -> -1)

(* OUnit test cases for both functions *)
module Tests = struct
  let suite = 
      "Tree Depth Tests" >:::
          [
              (* Tests for count_depth *)
              "should return 1 for a single leaf (count_depth)" >:: (fun _ ->
                  assert_equal 1 (try count_depth tree1 with _ -> -1));
              "should return 2 for a flat branch (count_depth)" >:: (fun _ ->
                  assert_equal 2 (try count_depth tree2 with _ -> -1));
              "should return 3 for a nested branch (count_depth)" >:: (fun _ ->
                  assert_equal 3 (try count_depth tree3 with _ -> -1));
              "should return 4 for a deeply nested branch (count_depth)" >:: (fun _ ->
                  assert_equal 4 (try count_depth tree4 with _ -> -1));
              "should return 4 for a complex tree (count_depth)" >:: (fun _ ->
                  assert_equal 4 (try count_depth tree5 with _ -> -1));
          ]
end

let () = ignore (run_test_tt_main Tests.suite)
