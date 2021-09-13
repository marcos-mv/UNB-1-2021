# f(X,[]) :- X is 0.
# f(X,[H|T]) :-
#     f(Y, T),
#     X is Y + (H mod 2).

f(X, []) :- X = 0.
f(X, [H|T]) :-
   f(Y, T),
   X is H*H + Y*Y.