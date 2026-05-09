# A Simple Project

Modify the given `Makefile` (in the `source/` folder) so that there are rules for the following targets.

- `all`
- `build`
- `sdist`
- `clean`

You may create additional rules. Here are the details for each rule.

## Rule for a target `all`

It must the default goal. When it is invoked, the executable files and the source distribution archive file are created. The recipe of this rule must be empty.

## Rule for a target `build`

A target that creates two executable files `othello-game` and `othello-game-debug`. The `othello-game` must be created by linking `main.o`, `game.o` and `othello.o`. The `othello-game-debug` must be created by linking `debug_main.o`, `game.o` and `othello.o`.

Any of the executable file should not be re-created unless the related source file (`.cpp` or `.hpp`) has been modified. Additionally, there must not be unnecessary compilation of a `.cpp` file when it was not changed.

Hint 1: A command that compiles and links in one step (e.g. `g++ *.cpp` or `g++ main.cpp game.cpp othello.cpp`) will not satisfy the above requirements.  
Hint 2: You will need to create at least two more targets (if you are leveraging GNU Make builtin targets). Otherwise, you will need to create six more targets.  
Hint 3: The recipe section of this target should be empty. Try to utilize the dependency graph of GNU Make.

## Rule for a target `sdist`

Create a compressed (with gzip) source distribution[^1] file with a name `othello-sdist.tar.gz` that can be used to build this project again. When this target is run while the source distribution file is already exist, the source distribution file should only be re-created when the other files has been modified.

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

- When the executable files are sensibly named `othello-game.exe` and `othello-game-debug.exe`, the grading script will fail. Just drop the `.exe` suffix when submit to run on GitHub.
- The grading script does not currently check if the Makefile will recompile and re-link the executables if any of the source file is changed. However, your `Makefile` should be able to handle this case.
