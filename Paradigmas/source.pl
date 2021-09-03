unb(X):- fga(X).

fga(ana).
fga(beto).
fga(carlos).


unb_report:-
    write('Estudantes da UNB: '),nl,
    unb(X),
    write(X), nl,
    fail.

nomes(marcos,joao,pedro,julio).

paciente('Maria Rita', 35, sus)
paciente('Pedro Silva', 70, amil)

