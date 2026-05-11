[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=19237037)
# Problem Objective:

Test the `evaluate()` function in "othello.cpp" in this game project.

You must supply at least three tests with meaningful coverage. Each test case must be in its own TEST_CASE macro. The file you should modify is `test_evaluate.cpp`.


## Tips:

* You will need to do the initialization steps before you can make calls to the function-under-test. You can use the `make_move(const string& move)` function to do all different test cases set up. Or pass in the board string directly to the constructor of Othello class. You can call the `display_status()` function in the test code to give you a visual guide for the black and white pieces status.
* There are some existing test cases for other part of the codebase. Feel free to take inspiration from them.
* The black piece is displayed as "x" and the white piece is displayed as "o".



## Submission:

Check in a single PDF file named "RESULTS.pdf" to the root folder in this project with the following content:

1. A written justification for the three or more tests you selected. Explain the criteria you used in determining test coverage.

2. Screenshot(s) of the output of the tests being run and passing.

Make sure that all changes are committed and push to GitHub Classroom repository, including the RESULTS PDF file and all changes to test files and other source files.

## About the Othello Project

### Build, Run, Run Test Cases

```console
mkdir build
cmake -S . -B build
cmake --build build
```

Run the program

```console
$ build/othello-game
```

Run the test cases

```console
$ build/tests/tests
Randomness seeded to: 3723841427
===============================================================================
No tests ran

$
```

Since we do not have any test cases written yet, the output is just telling us that there is no test cases to be run.


### Documentation

```console
cmake --build build --target docs
```
