# A Broken Shell

You are an intern in a small software company. You are tasked to create a Makefile that compiles one of their
projects written in C++17. Unfoutunately, due to the global pandemic, the company do not have enough
money to buy a license of a high-end shell program. Thus, you are stuck with a broken shell program that can only run a command
where you can only supplies one `.cpp` file as an argument to a command. The shell will also refuse to run any command containing an asterisk (`*`; ASCII code 42).

Write a `Makefile`, in the `source/` folder, that compiles this project using the shell with said limitations. Your Makefile must produce
an executable file with a name `money-printer`. You are not allowed to make any modification to the
codebase (e.g. renaming the file, changing the file content, etc.)

## Note

We (the grading script) will automatically use the broken-shell while testing your Makefile. There is no need to call the broken-shell before each command in the recipe yourself.
In fact, using the `./scripts/shell.py` may lead to unintended behaviors.

When the grading script runs your Makefile, the current working directory is `source/`. Its behavior is roughly equal to

```console
$ cd source/
$ make
```

## OS Compatability

This problem will only work on Unix-based operating systems.
