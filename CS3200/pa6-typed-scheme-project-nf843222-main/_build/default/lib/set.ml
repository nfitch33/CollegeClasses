open QCheck
open Util

(** A type that can be randomly generated and converted to string. *)
module type Type = sig
  include Show
  val gen : t arbitrary  (* qcheck generator for random values *)
end

(** Ordered types. *)
module type OType = sig
  include Type
  val le : t -> t -> bool (* less-than-or-equal-to, a ≤ b *)
end

(** Set interface. A module with type Set must provide all of the following: *)
module type Set = sig
  include Type                   (* the type of sets *)
  type elt                       (* the type of data elements *)
  val empty : t                  (* the empty set, ∅ *)
  val single : elt -> t          (* singleton set *)
  val insert : elt -> t -> t     (* insert a single element into a set *)
  val elem : elt -> t -> bool    (* check for membership of an element *)
  val of_list : elt list -> t    (* convert to set from list *)
  val to_list : t -> elt list    (* convert to list from set *)
  val union : t -> t -> t        (* union of two sets, a ∪ b *)
  val intersection : t -> t -> t (* intersection of two sets, a ∩ b *)
  val subset : t -> t -> bool    (* subset relation, a ⊆ b *)
  val eq : t -> t -> bool        (* equivalence relation, a ≃ b *)
  val inv : t -> bool            (* representation invariant *)
end
