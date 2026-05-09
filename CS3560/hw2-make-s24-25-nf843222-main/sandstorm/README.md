# Sandstorm

Now that [Ella Musk](https://genshin-impact.fandom.com/wiki/Ella_Musk) can speak Hilichurlian fluently, she set
her sight on [Mars](https://en.wikipedia.org/wiki/Mars). To prepare herself for Mars, she is training in the [Hypostyle Desert](https://genshin-impact.fandom.com/wiki/Hypostyle_Desert) in Sumeru.
However, the sandstorm in the desert is giving her a hard time. She hired you to write a Makefile
(not sure why she picked a Makefile of all things) that can warn her if the sandstorm is active or not.

A sandstorm is active when the modification date and time of the file `sandstorm.txt` is greater than
the file `calm.txt`. Sandstorm is not active otherwise.

In the given Makefile, write a rule that outputs `warning, a sandstorm is active!` when the sandstorm is active. Otherwise, it should
not output anything. We will run your Makefile with `--silent` option to help with the later case.

Hint: GNU Make itself relies heavily on the file's modication date/time, there is no need for an external shell command to find out
what the modification date/time of a file is. We will not deduct point if you are using said shell command, but it is not the intended solution.

## Note

When there is a sandstorm, aka.

```console
$ touch sandstorm.txt
```

The result should be

```conosle
$ make --silent
warning, a sandstorm is active!
```
