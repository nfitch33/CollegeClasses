# static-analysis

Perform the following steps.

1. Compile the source code in this folder, and make note of the issues found by the compiler. Submit this list of issues identified by the compiler.

2. Use two of the following static analysis tools to check the source code. Submit a list of issues identified by each of the tool.

- [Facebook's Infer](https://fbinfer.com/)
- [Cppcheck](https://cppcheck.sourceforge.io/)
- [clang-analyzer](https://clang-analyzer.llvm.org/) vis its `scan-build` command.
- [Flint++](https://github.com/JossWhittle/FlintPlusPlus)

3. Fix an error/warning found by the static analysis tools (from the step 2). Make a commit of the changes.

4. Show the updated list of issues to show that the issues were indeed fixed.

5. Reflect on the difference of the static analysis tool and the compiler. Discuss the pros and cons between the the compiler, and the two static analyzers.

## Submission

1. Prepare a report (e.g. a Microsoft Word document) with the following sections.
- A list of issues identified by the compiler.
- A list of issues from each of the static analysis tool you picked.
- The updated list of issues after the fix.
- A write-up discussing pros and cons between the compiler, and the two static analyzers.
2. Check in the report file into this folder (aka make a commit).
3. Make a commit of the fix if that have not been done already.
4. Push your commits to GitHub.
