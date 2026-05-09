# A Simple Project

You are given a codebase for a small C++17 project. Modify the given `Makefile`
(in the `source/` folder) so that there are rules for the following targets.

- `all`
- `build`
- `sdist`
- `clean`

You may create additional rules. Here are the details for each rule.

## Rule for a target `all`

It must be the default goal. When it is invoked, the executable files and the source distribution archive file are created. The recipe of this rule must be empty.

## Rule for a target `build`

A target that creates an executable file with a name `split-by`. The `split-by` must be created by linking `main.o` and `split_by.o`. However, its recipe section must be empty (e.g. no command in the recipe section). The executable file should not be re-created unless the related source file (`.cpp` or `.hpp`) has been modified.

Hint 1: The recipe section of this target should be empty. Try to utilize the dependency graph of GNU Make.

## Rule for a target `sdist`

Create a compressed (with gzip) source distribution[^1] file with a name `project-sdist.tar.gz` that can be used to build this project again. When this target is run while the source distribution file is already exist, the source distribution file should only be re-created when the other files has been modified.

## Rule for a target `clean`

This target removes all `.o` files and all the executable files. All `.o` files and all of the exeuctable files must be deleted even if some of them are already deleted before this target run. If you are on Windows and not using WSL, please use `$(RM)` instead of the `del` command.

[^1]: An archive file that contains the source code of the software. The archive file must have enough files that user can build the project again from this archive file.


## Note

The current directory that we will run your `Makefile` from is `source`. e.g.

```console
$ cd source/
$ make all
```

## Known Issues

- When the executable file is sensibly named `split-by.exe`, the grading script will fail. Just drop the `.exe` suffix when submit to run on GitHub.
- The grading script does not currently check if the Makefile will recompile and re-link the executables if any of the source file is changed. However, your `Makefile` should be able to handle this case.
