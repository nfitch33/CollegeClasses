likes(alice, bob).
likes(jane, john).
likes(bob, chris).
likes(chris, bob).

friends(X, Y):- likes(X, Y), likes(Y, X).