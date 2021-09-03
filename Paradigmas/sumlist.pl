# listsum(0, []).

# listsum(Result, [Head|Tail]) :-
#     listsum(SumOfTail, Tail),
#     Result is Head + SumOfTail.

# asserta(f([a,b,c],d)).

polygon(triangle, 3).
polygon(square, 4).
polygon(rectangle,4).
polygon(hexagon,6).

:- op(100, 'xf',has_four_sides).
has_four_sides(X):-
    polygon(X,4).