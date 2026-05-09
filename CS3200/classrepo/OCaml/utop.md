## `utop` example sessions

`utop` is a tool to access the OCaml [toplevel](https://cs3110.github.io/textbook/chapters/basics/toplevel.html).

Use command `#quit;;` to exit the interactive utop shell.

<img width="408" alt="Screenshot 2024-08-29 at 9 00 13 AM" src="https://github.com/user-attachments/assets/6437d4a3-cf75-4d49-8be7-bfa7c55aee28">

```
@drchangliu ➜ /workspaces/examples/ocaml (main) $ utop
───────────────────────────────────────────────────────────────────────────────┬─────────────────────────────────────────────────────────────┬────────────────────────────────────────────────────────────────────────────────
                                                                               │ Welcome to utop version 2.13.1 (using OCaml version 5.0.0)! │                                                                                
                                                                               └─────────────────────────────────────────────────────────────┘                                                                                

Type #utop_help for help about using utop.

─( 11:26:59 )─< command 0 >────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # let increment x = x + 1;;
val increment : int -> int = <fun>
─( 11:26:59 )─< command 1 >────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # increment 5;;
- : int = 6
─( 11:27:35 )─< command 2 >────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # 42;;
- : int = 42
─( 11:27:44 )─< command 3 >────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # let x = 42;;
val x : int = 42
─( 11:27:48 )─< command 4 >────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # let rec fact n = if n = 0 then 1 else n * fact (n - 1);;
val fact : int -> int = <fun>
─( 11:27:52 )─< command 5 >────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # fact 3;;
- : int = 6
─( 11:28:15 )─< command 6 >────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # fact 5;;
- : int = 120
─( 11:28:22 )─< command 7 >────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # fact 8;;
- : int = 40320
─( 11:28:25 )─< command 8 >────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # #quit;;
@drchangliu ➜ /workspaces/examples/ocaml (main) $ 
```

```
utop # #utop_help;;
If you can't see the prompt properly try: #utop_prompt_simple

utop defines the following directives:

#help            : list all directives
#utop_bindings   : list all the current key bindings
#utop_macro      : display the currently recorded macro
#utop_stash      : store all the valid commands from your current session in a file
#utop_save       : store the current session with a simple prompt in a file
#topfind_log     : display messages recorded from findlib since the beginning of the session
#topfind_verbose : enable/disable topfind verbosity

For a complete description of utop, look at the utop(1) manual page.
─( 07:30:40 )─< command 14 >────────────────────
```
