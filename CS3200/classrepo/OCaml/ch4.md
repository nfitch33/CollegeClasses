# Chapter 4. Higher-Order Programming - Highlights

* map. (list -> list)
* filter (list -> sub list)
* fold (list -> element)
* ch4.5 map, filter, fold on trees (ch4.5)
  * map (tree -> tree of same size and shape, easy!)
  * filter (harder. cutting out only matching nodes or the entire subtrees?)
  * fold (can be used to compute size, depth/height, preorder, and sum of tree) -- what if the init value needs to change as in list fold?

* ch4.4.1 combine: an abstract way of capturing and supporting the abstraction principle. Compare to design patterns, template libraries, framework vs libraries.
* ch4.7 curry and uncurry (all functions in OCaml can be broken down to repeated applications of functions with single parameters.)