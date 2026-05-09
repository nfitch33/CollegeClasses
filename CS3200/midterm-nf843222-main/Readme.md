## Midterm: Hands-on Part

During the exam, you only need to run:

```
ocamlc midterm.ml
./a.out
```

Your submission will be graded with

```
ocamlc -o grade midterm.ml midterm_grading.ml
./grade
```

Only a sample `midterm_grading.ml` is provided. The actual file used for grading will have a lot more test cases.

You are encouraged to add additional test cases. DO NOT modify the existing test code. Changing the parameter type or adding additional parameters to the functions-under-test will cause compilation errors during grading.

Eliminate all compilation errors and warnings before submission. Compilation errors will prevent grading code from successful completion. Points may be deducted for compilation warnings.

Make sure that at least your own test cases in your own "midterm.ml" compile and run. You may not receive partial credit for problems if your own "midterm.ml" fails to run.

Git-push-submission is the only thing needed for github. Your commit message should include your self assessment, e.g. "Solved 2 out of 3 problems with one additional partial solution. Expecting 80 out of 100 points."

