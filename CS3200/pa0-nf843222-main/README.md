[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=20642205)
# PA0: Introduction to OCaml

Your goal in this assignment is to familiarize yourself with OCaml, the programming language we'll be using for much of this course.

## Part 1: "Install OCaml"

Follow the instructions for [Homework0](https://github.com/OU-CS3200/cs3200/blob/main/Homework0.md).

## Part 2: Complete the Exercises

You will develop and submit your assignment through GitHub. 
The first step is to accept the assignment on Github classroom, which you already did.
This created a new private repository in which you should develop your solution. Clone the repository onto your local machine in order to begin working. 

## Submission
Your last commit to this repository before the due date will count as your assignment submission. If you forget how to use Git and/or GitHub, read more online (e.g., https://product.hubspot.com/blog/git-and-github-tutorial-for-beginners).

The template repository contains a `dune` (the standard OCaml build tool) project structure, including `bin/`, `lib/`, and `test/` directories. For this assignment, you may safely ignore the `bin/` and `test/` directories. Your job is to open the file `lib/lib.ml`, read the instructions, and complete the exercises contained within.

We use an automated testing framework, not only to make grading easier, but also to help guide your implementation. Run the command `dune test` at the command line to compile the project and evaluate the test cases. Your submission should pass all tests.

Initially, the provided code passes compilation and can run, but all tests would fail, as shown below. Your goal is to turn all red [FAIL] into green [OK]. 
```
>$ dune test
File "test/dune", line 2, characters 7-10:
2 |  (name pa0)
           ^^^
Testing `PA0'.
This run has ID `ZW531SV4'.

> [FAIL]        PA0          0   eucl_dist.
  [FAIL]        PA0          1   bool_and.
  [FAIL]        PA0          2   bool_or.
  [FAIL]        PA0          3   maj.
  [FAIL]        PA0          4   hello_world.
  [FAIL]        PA0          5   fib.

┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ [FAIL]        PA0          0   eucl_dist.                                                                                                                               │
└─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
[exception] Todo(_)
            Raised at Pa0__Util.todo in file "lib/util.ml", line 9, characters 2-19
            Called from Pa0__Lib.test_eucl_dist in file "lib/lib.ml", line 31, characters 32-59
            Called from Alcotest_engine__Core.Make.protect_test.(fun) in file "src/alcotest-engine/core.ml", line 186, characters 17-23
            Called from Alcotest_engine__Monad.Identity.catch in file "src/alcotest-engine/monad.ml", line 24, characters 31-35
            
Logs saved to `~/gitwork/pa0-drchangliu-1/_build/default/test/_build/_tests/PA0/PA0.000.output'.
 ─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────

Full test results in `~/gitwork/pa0-drchangliu-1/_build/default/test/_build/_tests/PA0'.
6 failures! in 0.001s. 6 tests run.
```


