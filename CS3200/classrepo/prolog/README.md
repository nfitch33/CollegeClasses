## Prolog Examples

Facts. Rules. Predicates. (A predicate is a function-like construct that represents a relationship or property. It’s defined by its name and arguments. Predicates can appear in both facts and rules.)

[The likes and friends example.](https://athena.ecs.csus.edu/~mei/logicp/prolog/programming-examples.html) 

The [8-puzzle problem](https://www.cpp.edu/~jrfisher/www/prolog_tutorial/5_2.html)

8 Kyu - Square Sum
https://www.codewars.com/kata/515e271a311df0350d00000f/solutions/prolog

7 Kyu - Odd or Even?
https://www.codewars.com/kata/5949481f86420f59480000e7/train/prolog

`=:=` and `=\=` (Arithmetic Equality and Inequality)

6 kyu - Who likes it?
https://www.codewars.com/kata/5266876b8f4bf2da9b000362/train/prolog


Tools: [Swi-prolog](http://www.swi-prolog.org); [OnlineGDB Prolog](https://www.onlinegdb.com/online_prolog_compiler); [Interactive Prolog](https://www.jdoodle.com/execute-prolog-online/)
```
likes(alice, bob).
likes(jane, john).
likes(bob, chris).
likes(chris, bob).

friends(X, Y):- likes(X, Y), likes(Y, X).
```
![Screenshot 2024-11-19 140723](https://github.com/user-attachments/assets/0401fbab-1c26-43b9-8589-d33a5378cf33)


```
find_max(X, Y, X) :- X >= Y, !.
find_max(X, Y, Y) :- X < Y.

find_min(X, Y, X) :- X =< Y, !.
find_min(X, Y, Y) :- X > Y.
```



```
GNU Prolog 1.5.0 (64 bits)
Compiled Jul 16 2021, 09:17:34 with gcc
Copyright (C) 1999-2021 Daniel Diaz

compiling /home/jdoodle.pg for byte code...
/home/jdoodle.pg compiled, 6 lines read - 821 bytes written, 6 ms
| ?- find_max(100,200,Max).


Max = 200

yes
| ?- find_min(100,200,Min).


Min = 100

yes
| ?- 
```

[The Hanoi Towers problem.](https://www.tutorialspoint.com/prolog/prolog_towers_of_hanoi_problem.htm)

Tool: [Prolog online](https://www.tutorialspoint.com/execute_prolog_online.php)
```
:- initialization(main).

move(1,X,Y,_) :-
   write('Move top disk from '), write(X), write(' to '), write(Y), nl.
move(N,X,Y,Z) :-
   N>1,
   M is N-1,
   move(M,X,Z,Y),
   move(1,X,Y,_),
   move(M,Z,Y,X).
   
main :- write('Starting ...\n'),
  move(4,source,target,auxiliary),
  write('The End.\n').
```


## Additional examples in this folder:

To install prolog on Linux, follow instructions on:
https://wwu-pi.github.io/tutorials/lectures/lsp/010_install_swi_prolog.html

If you don't want to install a local Prolog compiler,
run on https://www.onlinegdb.com/. Select "Prolog".

or

https://onecompiler.com/prolog/3zuvc54g4


```
@drchangliu ➜ /workspaces/examples/prolog (main) $ swipl
Welcome to SWI-Prolog (threaded, 64 bits, version 9.0.4)
SWI-Prolog comes with ABSOLUTELY NO WARRANTY. This is free software.
Please run ?- license. for legal details.

For online help and background, visit https://www.swi-prolog.org
For built-in help, use ?- help(Topic). or ?- apropos(Word).

?- [like].
true.

?- likes(alice, bob).
true.

?- friends(bob, chris).
true.

?- friends(chris, bob).
true.

?- friends(bob, bob).
false.

?- friends(alice, bob).
false.

?- halt.
@drchangliu ➜ /workspaces/examples/prolog (main) $ 
```
