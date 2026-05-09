# Odd or Even - The Makefile Edition

Implement the recipes of the target named `ItIsSurelyOdd` in the given `Makefile`. This target should output the word `odd`
when the number of files (exclude folders) in the current working directory is odd. Otherwise `even` should be output.

## Example Output

Running `make` results in the output `even`. For example,

```console
$ make
even
```

This is because there are two files: `Makefile` and `README.md`.

## Note - Grading script's behavior

The grading script will create a temporary folder and populate it with various amount of files and folders. It then copy your `Makefile` into this temporary folder. This behavior is roughly

```console
$ mkdir -p temporary-folder/
$ (randomly populate temporary-folder/ with files and folders)
$ cp Makefile temporary-folder/answer.mk
$ cd temporary-folder/
$ make -f answer.mk
```
