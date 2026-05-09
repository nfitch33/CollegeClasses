# CS3200-PA5-Scheme1

Search for `todo` tasks in the file `lib/lib.ml` and implement them.

To play with the code, run:
```
dune utop lib
utop # open Pa5__Lib;;
utop # ShowExp.show ex5;;
- : string = "(EBinexp BAdd (VFloat 3.) (VFloat 100.))"
utop # open ShowExp;;
utop # show ex6;;
- : string = "(EBinexp BSub (VFloat 3.) (VFloat 100.))"
utop # free "x" ex5;;    (* The result should be true. *)
Exception: Todo _.
utop # show ex35;;  (*   The result should be false. *)
- : string = "(ELet x (VFloat 6.) (EIte (VBool false) (VFloat 5.) x))"
utop # free "x" ex35;;
Exception: Todo _.
utop # #quit;;
```

Your initial build should look like this.

```
changliu@Changs-Mac-Studio cs3200-pa5-template % dune clean
changliu@Changs-Mac-Studio cs3200-pa5-template % dune test
File "test/dune", line 2, characters 7-10:
2 |  (name pa5)
           ^^^
Testing `PA5'.
This run has ID `KESRL4VK'.

> [FAIL]        test            0   free.
  [FAIL]        test            1   parse.
  [FAIL]        test            2   desugar.
  [FAIL]        test            3   interp.
  [FAIL]        test            4   run_fail.
  [FAIL]        test            5   run_pass.

┌──────────────────────────────────────────────────────────────────────────────┐
│ [FAIL]        test            0   free.                                      │
└──────────────────────────────────────────────────────────────────────────────┘
[exception] Todo(_)
            Raised at Pa5__Util.todo in file "lib/util.ml", line 58, characters 2-19
            Called from Pa5__Lib.(fun) in file "lib/lib.ml", line 185, characters 32-55
            Called from Alcotest_engine__Core.Make.protect_test.(fun) in file "src/alcotest-engine/core.ml", line 180, characters 17-23
            Called from Alcotest_engine__Monad.Identity.catch in file "src/alcotest-engine/monad.ml", line 24, characters 31-35
            
Logs saved to `~/cs3200/cs3200-pa5-template/_build/default/test/_build/_tests/PA4/test.000.output'.
 ──────────────────────────────────────────────────────────────────────────────

Full test results in `~/cs3200/cs3200-pa5-template/_build/default/test/_build/_tests/PA5'.
6 failures! in 0.001s. 6 tests run.
changliu@Changs-Mac-Studio cs3200-pa5-template % 
```



### Desugaring (Ch10.3)
The following lines are equivalent:
```
let x = e1 in e2
((fun x -> e2) e1)
(e3 e1)   (* e3 is (fun x -> e2) *)
```


