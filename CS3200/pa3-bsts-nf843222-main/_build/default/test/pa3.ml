open QCheck
open QCheck_alcotest

open Pa3__Lib
open Pa3__Util
open Pa3__Set


module Int : OType = struct
  type t = int
  let le = (<=)
  let gen = small_int
  let show = string_of_int
end

module type Name = sig
  val name : string
end

module SetTest =
  functor (N : Name) (T : OType)
            (F : functor (T : OType) -> Set with type elt = T.t) -> struct
    let tests =
      let module LS = ListSet(T) in
      let module S = F(T) in
      let open S in
      List.map to_alcotest [

          (* [∀ x, x ∈ { x }] *)
          QCheck.Test.make ~name:(N.name ^ "_elem_single") ~count:100
            T.gen (fun a -> elem a (single a));

          (* [∀ a, of_list (to_list a) ≃ a] *)
          QCheck.Test.make ~name:(N.name ^ "_from_list_to_list") ~count:100
            S.gen (fun a -> eq (of_list (to_list a)) a);

          (* [∀ l, to_list (of_list l) ≃ l] *)
          QCheck.Test.make ~name:(N.name ^ "_to_list_from_list") ~count:100
            (small_list T.gen) (fun l -> assume (nodup l);
                                         LS.eq (to_list (of_list l)) l);

          (* [∀ a b, of_list a ∪ of_list b ≃ of_list (a @ b)] *)
          QCheck.Test.make ~name:(N.name ^ "_union_of_list") ~count:100
            (pair (small_list T.gen) (small_list T.gen))
            (fun (a, b) -> eq (union (of_list a) (of_list b)) (of_list (a @ b)));

          (* [∀ a b, of_list a ∩ of_list b ≃ of_list (List.filter (fun x -> List.mem x a) b)] *)
          QCheck.Test.make ~name:(N.name ^ "_intersection_of_list") ~count:100
            (pair (small_list T.gen) (small_list T.gen))
            (fun (a, b) -> eq (intersection (of_list a) (of_list b))
                             (of_list (List.filter (fun x -> List.mem x a) b)));

          (* [∀ a, a ⊆ a] *)
          QCheck.Test.make ~name:(N.name ^ "_subset_refl") ~count:100
            S.gen (fun a -> subset a a);

          (* [∀ a b c, a ⊆ b → b ⊆ c → a ⊆ c] *)
          QCheck.Test.make ~name:(N.name ^ "_subset_trans") ~count:400
            (triple S.gen S.gen S.gen)
            (fun (a, b, c) -> assume (subset a b && subset b c); subset a c);

          (* [∀ a b, a ⊆ b ∧ b ⊆ a ⇔ a ≃ b] *)
          QCheck.Test.make ~name:(N.name ^ "_subset_eq") ~count:200
            (pair S.gen S.gen) (fun (a, b) -> (subset a b && subset b a) = eq a b);

          (* [∀ a, ∅ ∪ a ≃ a] *)
          QCheck.Test.make ~name:(N.name ^ "_empty_identity_l") ~count:100
            gen (fun a -> eq (union empty a) a);

          (* [∀ a, a ∪ ∅ ≃ a] *)
          QCheck.Test.make ~name:(N.name ^ "_empty_identity_r") ~count:100
            gen (fun a -> eq (union a empty) a);

          (* [∀ a, ∅ ∩ a ≃ ∅] *)
          QCheck.Test.make ~name:(N.name ^ "_empty_annihilator_l") ~count:100
            gen (fun a -> eq (intersection empty a) empty);

          (* [∀ a, a ∩ ∅ ≃ ∅] *)
          QCheck.Test.make ~name:(N.name ^ "_empty_annihilator_r") ~count:100
            gen (fun a -> eq (intersection a empty) empty);

          (* [∀ a, a ∪ a ≃ a] *)
          QCheck.Test.make ~name:(N.name ^ "_union_idempotent") ~count:100
            gen (fun a -> eq (union a a) a);

          (* [∀ a b, a ∪ b ≃ b ∪ a] *)
          QCheck.Test.make ~name:(N.name ^ "_union_comm") ~count:200
            (pair gen gen) (fun (a, b) -> eq (union a b) (union b a));

          (* [∀ a b c, a ∪ (b ∪ c) ≃ (a ∪ b) ∪ c] *)
          QCheck.Test.make ~name:(N.name ^ "_union_assoc") ~count:400
            (triple gen gen gen)
            (fun (a, b, c) -> eq (union a (union b c)) (union (union a b) c));

          (* [∀ a b, a ∩ b ≃ b ∩ a] *)
          QCheck.Test.make ~name:(N.name ^ "_intersection_comm") ~count:200
            (pair gen gen) (fun (a, b) -> eq (intersection a b) (intersection b a));

          (* [∀ a b c, a ∩ (b ∩ c) ≃ (a ∩ b) ∩ c] *)
          QCheck.Test.make ~name:(N.name ^ "_intersection_assoc") ~count:400
            (triple gen gen gen)
            (fun (a, b, c) -> eq (intersection a (intersection b c))
                                (intersection (intersection a b) c));

          (* [∀ a b c, a ∩ (b ∪ c) ≃ (a ∩ b) ∪ (a ∩ c)] *)
          QCheck.Test.make ~name:(N.name ^ "_distr_l") ~count:400
            (triple gen gen gen)
            (fun (a, b, c) -> eq (intersection a (union b c))
                                (union (intersection a b) (intersection a c)));

          (* [∀ a b c, (a ∪ b) ∩ c ≃ (a ∩ c) ∪ (b ∩ c)] *)
          QCheck.Test.make ~name:(N.name ^ "_distr_r") ~count:400
            (triple gen gen gen)
            (fun (a, b, c) -> eq (intersection (union a b) c)
                                (union (intersection a c) (intersection b c)))
        ]
  end

let () =
  let module LName = struct let name = "list" end in
  let module LSetTest = SetTest(LName)(Int)(ListSet) in

  let module LSet = ListSet(Int) in
  let () = add_qcheck @@
             QCheck.Test.make ~name:"ListSet_inv_insert" ~count:1600
               (pair Int.gen LSet.gen)
               (fun (x, l) -> assume (nodup l);
                              nodup (LSet.insert x l)) in

  let module BName = struct let name = "bst" end in
  let module BSet = BstSet(Int) in
  let module BSetTest = SetTest(BName)(Int)(BstSet) in

  let () = add_qcheck @@
             QCheck.Test.make ~name:"BstSet_inv_insert" ~count:1600
               (pair Int.gen BSet.gen)
               (fun (x, s) -> assume (bst_inv Int.le s);
                              bst_inv Int.le (BSet.insert x s)) in

  let module RBName = struct let name = "rbt" end in
  let module RBSet = RbtSet(Int) in
  let module RBSetTest = SetTest(RBName)(Int)(RbtSet) in

  let () = add_qcheck @@
             QCheck.Test.make ~name:"RbtSet_inv_insert" ~count:1600
               (pair Int.gen RBSet.gen)
               (fun (x, s) -> assume (rbt_inv Int.le s);
                              rbt_inv Int.le (RBSet.insert x s)) in

Alcotest.run "PA3" [
  ("test", !tests);
  ("qcheck", !qcheck_tests);
  ("ListSet", LSetTest.tests);
  ("BstSet", BSetTest.tests);
  ("RbtSet", RBSetTest.tests);
  ("LLM_Union", Llm_test.llm_union_tests);
  ("LLM_ListSet_Inter", Llm_test.llm_list_intersection_tests);
  ("LLM_BstSet_Inter", Llm_test.llm_bst_intersection_tests);
  ("LLM_RbtSet_Inter", Llm_test.llm_rbt_intersection_tests);  
]

