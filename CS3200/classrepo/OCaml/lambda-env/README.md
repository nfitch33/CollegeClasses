```console
─( 16:41:38 )─< command 1 >──────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # open Interp;;
─( 16:49:02 )─< command 2 >──────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # open Main;;
─( 16:49:06 )─< command 3 >──────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # open Ast;;
─( 16:49:09 )─< command 4 >──────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # parse "1+1";;
Exception: Failure "lexing: empty token".
─( 16:49:11 )─< command 5 >──────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # parse "(fun b -> b)";;
- : expr = Fun ("b", Var "b")
─( 16:51:29 )─< command 6 >──────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # parse "(fun b -> b)" |> eval;;
Error: This expression has type expr but an expression was expected of type
         env = value Env.t
─( 16:52:15 )─< command 7 >──────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # parse "(fun b -> b)" |> eval Env.empty;;
- : value = Closure ("b", Var "b", <abstr>)
─( 16:52:54 )─< command 8 >──────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # parse     "(fun x -> \
     (fun f -> \
     (fun x -> \
     f (fun a -> a)) \
     (fun c -> c)) \
     (fun y -> x)) \
     (fun b -> b)"
;;
- : expr =
App
 (Fun ("x",
   App
    (Fun ("f",
      App (Fun ("x", App (Var "f", Fun ("a", Var "a"))), Fun ("c", Var "c"))),
    Fun ("y", Var "x"))),
 Fun ("b", Var "b"))
─( 16:52:54 )─< command 9 >───────────────────────────
utop # parse     "(fun x -> \
     (fun f -> \
     (fun x -> \
     f (fun a -> a)) \
     (fun c -> c)) \
     (fun y -> x)) \
     (fun b -> b)" |> eval Env.empty;;
- : value = Closure ("b", Var "b", <abstr>)
─( 09:12:06 )─< command 10 >──────────────────────────
