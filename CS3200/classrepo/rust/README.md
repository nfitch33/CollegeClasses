```
@drchangliu ➜ /workspaces/examples/rust (main) $ rustc print10.rs 
@drchangliu ➜ /workspaces/examples/rust (main) $ ls
hello-world  print10  print10.rs
@drchangliu ➜ /workspaces/examples/rust (main) $ ./print10
0
1
2
3
4
5
6
7
8
9
@drchangliu ➜ /workspaces/examples/rust (main) $ valgrind ./print10
==9576== Memcheck, a memory error detector
==9576== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==9576== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==9576== Command: ./print10
==9576== 
0
1
2
3
4
5
6
7
8
9
==9576== 
==9576== HEAP SUMMARY:
==9576==     in use at exit: 0 bytes in 0 blocks
==9576==   total heap usage: 12 allocs, 12 frees, 3,109 bytes allocated
==9576== 
==9576== All heap blocks were freed -- no leaks are possible
==9576== 
==9576== For lists of detected and suppressed errors, rerun with: -s
==9576== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
@drchangliu ➜ /workspaces/examples/rust (main) $ 
```