[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=19225104)
<h2 align="center">
CS3560 Homework Assignment - Unit Testing (100 Points)<br/>
Due date: Please check the entry on Canvas
</h2>

In this homework, you will

- Learn how to work with a CMake project.
- Learn how to add a third-party library to a CMake project with `FetchContent`.
- Learn how to work with Catch2's default main implementation.
- Write test cases for the `gpa()` method of class `College` in a file `college.cpp`
- Write test cases for the `hours()` method of class `College` in a file `college.cpp`

## Optional Reading Assignments

- Review/work through the five tutorials (0 to 4) about CMake in [`cmake.examples/` folder in OU-CS3560/examples repository](https://github.com/OU-CS3560/examples/tree/main/cmake.examples). If you want, you can
  watch/look up other tutorials about CMake, but keep in mind that we are using CMake version >= 3.16.

## Required Software Packages

- C++ Compiler.
- CMake.
- GNU Make.
- If you are working on Windows, we are expected that this homework is done in WSL. The above software packages are to be installed in WSL.

## Step 1 - Configuring a CMake Project

To build a CMake project, there are two major steps:

- Configure the project and create the build system files.
- Actually build the project.

As we mentioned before in the lecture, CMake is a meta-build system. It does not build the project, but it delegates this task to the actual build system. Hence the term "meta-build system" and the need for GNU Make.

This section will discuss the configuration and build system files generation. The command to do that is

```console
cmake -S . -B build -G "Unix Makefiles"
```

This command will configure the project and generate build files using "Unix Makefiles" generator. The `-S .` flag
tells CMake that we will use the
current working directory for where the source files are.

The `-B build` flag tells CMake that we will be using
out-of-source build approach and we want CMake to store all build files in the folder called `build`. This
keeps the source files from mixing up with the build-related files (e.g. object files).

The `-G "Unix Makefiles"` flag instructs CMake to use GNU Make as a build system and generates its Makefiles accordingly.

For an example output
of this command and other commands in this section, please see [Appendix B](#appendix-b---example-output-from-step-1).

**Your task for this step:**

1. Make sure that you are in the root of this repository then run `cmake -S . -B build -G "Unix Makefiles"` (if you have not run it already).

## Step 2 - Build a CMake Project

Once the project is configured and the build system is generated, we can instruct CMake to build the project with

```console
cmake --build build
```

The above command is equivalent to "compiling" the program, so if you make changes
to the code, you need to re-run that command to "re-compilie" the program.

If you inspect the content of the `build/` folder, you will see a file `college-app`
which is our executable defined in the main `CMakeLists.txt` file.

We can run this executable file as followed.

```console
krerkkiat@odd01.cs.ohio.edu:~/hw-unit-testing-krerkkiat $ ./build/college-app
Welcome to Ohio State University Course Management.

Begin by entering your username: herta
Now Enter Your Full name: Herta

... (part of the output was omitted for brevity) ...
```

## Step 3 - Fixing the Output Inconsistency and Re-building the Project

You may notice that the output says `Ohio State University` instead of `Ohio University`. We want to make sure that it says `Ohio University`.

**Your tasks in this step:**

1. Fix the incorrect university name, re-compile (using the `cmake --build build`). The name
   of the university in the output should be `Ohio University`.
2. Re-run the executable and take a screenshot of the command and its output that shows that
   university's name in the output is now corrected.
3. Add this screenshot to this repository (aka making a commit).

## Step 4 - Adding Catch2

In this step, you will be adding Catch2 to the project. We will be using CMake library called `FetchContent`. It allows you to fetch source code from various source. In this assignment you will be using its [`FetchContent_Declare`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_declare) and [`FetchContent_MakeAvailable`](https://cmake.org/cmake/help/latest/module/FetchContent.html#command:fetchcontent_makeavailable) function to obtain Catch2 source code.

Here is an example of using `FetchContent_Declare` to obtain the source code of `cxxopts` library.

```cmake
FetchContent_Declare(
  cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
  GIT_TAG        v3.1.1
)
```

The first argument is the name that we will be using to refer to it in `FetchContent_MakeAvailable`. The `GIT_REPOSITORY` term tells `FetchContent_Declare` that the next argument is a url to a Git repository. Similarly we can use `GIT_TAG` to specify that the next argument is the tag we want to pull from.

The `cxxopts` is not ready for use just yet, we need to make it available using `FetchContent_MakeAvailable`. This function takes a name (or multiple names separated by a space). For example, to make `cxxopts`, we can call it like so

```cmake
FetchContent_MakeAvailable(cxxopts)
```

If we have two names we want to make available (say `name1` and `name2`), we can call the function as shown below to
make both names available.

```cmake
FetchContent_MakeAvailable(name1 name2)
```

**Your tasks:**

1. Using `FetchContent_Declare`, tell CMake to retrieve the source code
   of Catch2 version `v3.7.1` from `https://github.com/catchorg/Catch2.git`. Use `Catch2` as the function first argument.
2. Modify the existing `FetchContent_MakeAvailable` to make this new `Catch2` name
   available to the project.
3. Run `cmake -S . -B build -G "Unix Makefiles"` to re-configure the project. Make sure there is no
   error in it. If there is error, fix them before moving on to the next step.

## Step 5 - Add a Test Program

A test program is just another executable of the project. The one we were working with in the previous steps
is created by these function calls.

```cmake
add_executable(college-app main.cpp)
target_link_libraries(college-app lib cxxopts)
```

The first function, [`add_executable(<target-name> <source-files>)`](https://cmake.org/cmake/help/latest/command/add_executable.html), tells CMake that we want an executable named `<target-name>` and its source files are `<source-files>`.
The [`target_link_libraries(<target-name> <names>)`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html) links `<names>` to the first argument (the `<target-name>`). In this case, we create `college-app` from `main.cpp` file and later link this executable file with `lib` and `cxxopts`. The target `lib` contains `course` and `college`.

Catch2 provides a main function for us already and this is available via `Catch2::Catch2WithMain` target that we can link against.

**Your tasks:**

1. Add an executable named `tests` with `test_college.cpp` as its source file.
2. Link this `tests` target to `lib` and `Catch2::Catch2WithMain`.
3. Re-build the project.
4. Run the `tests` executable and take screenshot of the command and its output.
5. Add said screenshot into this repository (aka making a commit).

## Step 6 - Write a Simple Test Case for `College::hours` Class

In this step, you will be writing a simple test case for `College::hours`. We will be using [`TEST_CASE`](https://github.com/catchorg/Catch2/blob/v3.7.1/docs/test-cases-and-sections.md#test-cases-and-sections) macro, so start by
adding necessary include files.

```c++
#include <catch2/catch_test_macros.hpp>
#include "college.hpp"

using namespace Catch;
```

Next, add a simple test case that test if the total hours is `0.0`.

```c++
TEST_CASE("hours of no classes must be 0") {
  // TO BE COMPLETE LATER ON IN THIS SECTION.
}
```

Next we can create the `College` object. Add the following statement in `TEST_CASE` macro we created.

```c++
College college = College("Ohio University");
```

To make sure that the constructor work, we can add a call to `CHECK` macro that test if the name is assigned properly (thus the object is created properly). Add the following statement in `TEST_CASE` macro we created.

```c++
CHECK(college.get_college_name() == "Ohio University");
```

`CHECK` is equivalent to the `REQUIRE` you see in the lecture, but the test case is aborted right away when the test failed.

To test a floating point number we need to use [floating Matcher](https://github.com/catchorg/Catch2/blob/v3.7.1/docs/comparing-floating-point-numbers.md#top), and since we are using a [matcher](https://github.com/catchorg/Catch2/blob/v3.7.1/docs/matchers.md#top), we need to use [`REQUIRE_THAT`](https://github.com/catchorg/Catch2/blob/v3.7.1/docs/assertions.md#matcher-expressions) instead of the normal [`REQUIRE`](https://github.com/catchorg/Catch2/blob/v3.7.1/docs/assertions.md#natural-expressions).

To test if the hours is `0.0` with a margin of `0.001` we can use `WithinAbs` matcher as shown below.

```c++
// Add the necessary header and use the namespace after the current include statements.
#include <catch2/matchers/catch_matchers_floating_point.hpp>

// Add this after the current using namespace statement.
using namespace Catch::Matchers;

// In our TEST_CASE, add the test using the matcher expression.
REQUIRE_THAT(college.hours(), WithinAbs(0.0, 0.001));
```

Again, we can rebuild the project with `cmake --build build` and run the `tests` executable.

```console
$ cmake --build build
... (output is omitted for brevity) ...
$ ./build/tests
Randomness seeded to: 3687295713

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tests is a Catch2 v3.7.1 host application.
Run with -? for options

-------------------------------------------------------------------------------
hours of no classes must be 0
-------------------------------------------------------------------------------
/home/krerkkiat/hw-unit-testing-krerkkiat/test_college.cpp:16
...............................................................................

/home/krerkkiat/hw-unit-testing-krerkkiat/test_college.cpp:20: FAILED:
  REQUIRE_THAT( college.hours(), WithinAbs(0.0, 0.001) )
with expansion:
  1.0 is within 0.001 of 0.0

===============================================================================
test cases: 1 | 1 failed
assertions: 2 | 1 passed | 1 failed
```

The output shows that the test case failed. Your task is to identify and fix this bug.

**Your tasks:**

1. Identify and fix the bug in `College::hours`.
2. Rebuild the project.
3. Run the `tests` executable and take screenshot of the command and its output. The test case must now be passing.
4. Add the changes to `test_college.cpp` and said screenshot into this repository (aka making a commit).

## Step 7 - Write Test Cases for `College::gpa()`

In this step, you will be writing test cases that test `College::add()` member function. Implement

- Two different test cases that cover the inputs that resulted GPA is `0.0`.
- Two different test cases that cover the inputs that resulted GPA is `4.0`.

**Your tasks**

1. In `test_college.cpp`, implement the four test cases specified above.
2. Rebuild the project.
3. Run the test program and take a screenshot of the command and its output. The test cases must be passing.
4. Add the changes to `test_college.cpp` and said screenshot into this repository (aka making a commit).

## Submissions

- Push all the commits to GitHub.
- Submit your repository URL to Canvas.

## Appendix A - Tips

### Hint on writing test cases

Keep in mind that there are three main steps in each test case.

1. Prepare the object to be tested and/or prepare the in input data to be used in the test and/or prepare the expected output.
2. Perform the action by calling the member function. This step usually is just one line, but it can be multiple lines.
3. *Test* that the result from step 2 is as expected.

Here are some tips for each step.

1. **Preparing the `College` object**. There are at least two methods to prepare your `College` object for a test.
   - *Manually create related objects*: In this method, we are creating an empty `College` object.
     We then create all the `Course` objects, and add them to our `College` object using `College::add` method.
   - *Use the `College::load` method*: Since the `College::load` method is taking `std::istream&`, we can prepare
     string stream and pass it to the method instead of an input stream of a file. If you are using an input file, make sure that
     the input file is checked into the repository.
2. **Perform the action**. This step should be trivial, but if you need hint, it is that we call the `gpa` method on our prepared `College` object.
3. **Test the result**. So far we only see `REQUIRE` being used, but there are other macros you can use e.g. `REQUIRE_FALSE`,  `REQUIRE_THAT`, etc. In this case, you want to look into [Floating point comparisons](https://github.com/catchorg/Catch2/blob/v3.7.1/docs/comparing-floating-point-numbers.md#top)
since the value returned from the `Colelge::gpa()` is floating point number.

For information about other macros, please visit [Catch2 Reference](https://github.com/catchorg/Catch2/tree/v3.7.1/docs#reference) page.

### IntelliSense Cannot Find the Header Files for Catch2

- Delete the `build` folder and re-configure and re-build the project (`cmake -S . -B build -G "Unix Makefiles"` then `cmake --build build`). Make sure there is no error and the folder is called `build` (we hard coded the folder name for the configuration).
- (this assumes that you are using vscode) Open the problematic file then restart IntelliSense by running the command
   "C/C++: Restart IntelliSense for Active File" using the [vscode command palette](https://code.visualstudio.com/docs/getstarted/userinterface#_command-palette).
- (this assumes that you are using vscode) Manually adding the include paths to the  "C/C++ Configuration". Open the configuration UI by invoking "C/C++: Edit configurations (UI)" command from the command palette. Under the "Include Path" section, add `${workspaceFolder}/build/_deps/catch2-src/src` on a new line.
- Stop by and talk to us after class since this will be easier to solve in-person than over email messages.

### Codebase Documentation

A rough specification of the codebase is in `docs/2401fal15proj3.docx`.

## Appendix B - Example output from step 1

An example output of `cmake -S . -B build -G "Unix Makefiles"` before we modifying the main `CMakeLists.txt` file.

```console
$ pwd
/home/krerkkiat/hw-unit-testing-krerkkiat
$ cmake -S . -B build -G "Unix Makefiles"
-- The CXX compiler identification is GNU 14.2.1
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (7.6s)
-- Generating done (0.0s)
-- Build files have been written to: /home/krerkkiat/hw-unit-testing-krerkkiat/build
$
```

## Appendix D - Rubric

Total points: 100

- (20 points) Students demonstrate that they can work with CMake project (configuring, building and re-building).
- (10 points) Students demonstrate that they can add third-party library using `FetchContent`.
- (10 points) Base on the failing test case's output, students are able to analyze the codebase for bugs and apply the fix.
- (30 points) Students demonstrate that they can implement test cases to cover part of the input space that resulted in `0.0` GPA.
- (30 points) Students demonstrate that they can implement test cases to cover part of the input space that resulted in `4.0` GPA.
