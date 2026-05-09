# Problem 2 and 3

There are two problems in this folder.

## Problem 2 - Your Own wc Implementation

You may use the provided project structure, or use your own codebase.

1. Implement the `countLine` and `countChar` functions.
   
   - `int countLine(string text)` returns the number of new-line characters in its argument. It also write to standard output: `“XXX Lines` where `XXX` is the number of lines in the parameter.
   - `int countChar(string text)` returns the number of characters in its argument. It also write to standard output: `“XXX Characters` where `XXX` is the number of characters found.

2. Implement the `main` function that

   - Take one command line argument and treat it as a path to an input file. If no command line argument is given, the progrm outputs an error message.
   - Read the content from the file path from the command line argument.
   - Call `countLine` and `countChar` with the content read from the file.

3. Make a commit of your source code.
4. Add Doxygen to the project and document both `countLine` and `countChar` functions. Use at least one Doxygen special command.
5. Make a commit of your work in step 4.
6. Write a report for this problem (PDF or Microsoft Word) with answers to the following questions

   - Q1: With a static analysis tool of your choice (pick one from cppcheck, flint++, clang-analyzer via its `scan-build` command, or Facebook's Infer), **show with screenshots** that there is no problem with your source code.
   - Q2: With Valgrind, **show screenshots of its output** that prove that there is no problem with your program when running with `data/input5.txt`.
   - Q3: Run doxygen to generate documentation and **show screenshots** that both functions are rendered properly.

7. Add the report to this folder. Make a commit of this report file.
8. Push your commits out to GitHub.

## Problem 3 - Add Test Cases with Catch2

1. Add Catch2 to the CMake project and add `tests` executable with a proper library linked.
2. Write a test case for `countLine`.
3. Write a test case for `countChar`.
4. Make a commit of your source code.
5. Write a report (PDF or Microsoft Word) that answers the following questions

   - Q4: Show, **using screenshots**, that all your test cases are passing. Catch2 must report 2 test cases were run in the screenshots.

6. Add the report to this folder. Make a commit.
7. Push your commits out to GitHub.

## Tips

- You are free to combine the two reports, but please make sure that the sections are clear.
- You are free to use code segments from any existing open source code for this program, including open source code for `wc` that you can find anywhere. (Just FYI, [https://www.dropbox.com/s/9000njf4b903vth/wc.cc?dl=0](https://www.dropbox.com/s/9000njf4b903vth/wc.cc?dl=0). However, this source code usually lead to more confusion since it is written in C).

## Appendix A - Frequently Asked Questions (FAQs)

Q: I do not know how to implement command line argument in C++  
A: Please review [https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/](https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/) if you want to do it manually or [https://github.com/jarro2783/cxxopts](https://github.com/jarro2783/cxxopts) if you want to use `cxxopts`.  

Q: Are the program supposed to create file?  
A: No. However, when you are writing your test cases, you can create files if needed (either manually or programmatically before the test cases are run).  
