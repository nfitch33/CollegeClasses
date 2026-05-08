### CS3200 Final Exam (Hands-on Part)

There are several independent programs in this folder. All problems weigh equally.
Make sure you complete all of them separately.

At least 5 test cases with meaningful coverage are required for each problem. 

You are encouraged to add at least one new test case for each problem.

Your programs may be tested with additional secret test cases during grading.

To compile and test the programs, use commands similar to the following example.

```
ocamlfind ocamlc -o factorial -package oUnit -package num -linkpkg -g factorial.ml
```

#### dune
To use `dune` to build and run, use commands such as the following:
```console
dune clean
dune build
dune exec ./factorial.exe
```
Replace `factorial.exe` with the actual exe file name.

DO NOT submit code that does not compile or runs forever. You may not get partial credit when that happens.

DO NOT commit binary files or non-source-code files to the code repository. 
