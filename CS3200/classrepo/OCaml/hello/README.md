```
(base) changliu@S8:~/gitwork/cs3200/OCaml/hello$ rm a.out
(base) changliu@S8:~/gitwork/cs3200/OCaml/hello$ ls
_build  dune  dune-project  hello2.ml  hello.cmi  hello.cmo  hello.ml  test.cmi  test.cmo
(base) changliu@S8:~/gitwork/cs3200/OCaml/hello$ ocamlc hello.ml
(base) changliu@S8:~/gitwork/cs3200/OCaml/hello$ ls
a.out  _build  dune  dune-project  hello2.ml  hello.cmi  hello.cmo  hello.ml  test.cmi  test.cmo
(base) changliu@S8:~/gitwork/cs3200/OCaml/hello$ ./a.out
Hello World!
from CompSci3200
from CS 3200
(base) changliu@S8:~/gitwork/cs3200/OCaml/hello$ ocamlc hello2.ml
(base) changliu@S8:~/gitwork/cs3200/OCaml/hello$ ./a.out
Hello World!
from CS3200
from CS 3200
(base) changliu@S8:~/gitwork/cs3200/OCaml/hello$ \rm -rf _build/
(base) changliu@S8:~/gitwork/cs3200/OCaml/hello$ ls
a.out  dune  dune-project  hello2.cmi  hello2.cmo  hello2.ml  hello.cmi  hello.cmo  hello.ml  test.cmi  test.cmo
(base) changliu@S8:~/gitwork/cs3200/OCaml/hello$ dune build
(base) changliu@S8:~/gitwork/cs3200/OCaml/hello$ ls
a.out  _build  dune  dune-project  hello2.cmi  hello2.cmo  hello2.ml  hello.cmi  hello.cmo  hello.ml  test.cmi  test.cmo
(base) changliu@S8:~/gitwork/cs3200/OCaml/hello$ cat dune
(executable
 (name hello))(base)
changliu@S8:~/gitwork/cs3200/OCaml/hello$ cat dune-project
(lang dune 3.4)(base)
(base) changliu@S8:~/gitwork/cs3200/OCaml/hello$ dune exec ./hello.exe
Hello World!
from CompSci3200
from CS 3200
changliu@S8:~/gitwork/cs3200/OCaml/hello$ dune exec ./hello
Error: Program "./hello" not found!
(base) changliu@S8:~/gitwork/cs3200/OCaml/hello$ opam switch list
#  switch  compiler                    description
→  cs3200  ocaml-base-compiler.4.14.0  cs3200
(base) changliu@S8:~/gitwork/cs3200/OCaml/hello$
```
