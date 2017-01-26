Implementation de { FC (Look ahead) + heurisitique MD, BJ (Look back) + MC }

Générateur de pigeon(number pigeons);
Générateur de dame(number dames);

-- ajouter temps d'éxecution --

=> fichier .txt

exemple :

0 : a b c
1 : a c
2 : a b
3 : ...
[...]
m - 1 : a b c

(1,2) :
a b
a c
b c
(2,3) :
b c
b a
[...]


///// PIGEON

vars : 0 .. n-1 (entiers)
valeurs : 0 .. m-1 (entiers)

codage des domaines ( matrice n * m )

tableau [ var ] [ valeurs ] rempli de booléen ( en C => 1 ou 0 et non true ou false )

D(i,j) = { 1 si val j € Dj | 0 si valeur j /€/ Dj }



codage des contraintes & relations

matrices de contraintes C ( n * n )

tableau [ var ] [ var ]

Si pas de contraintes entre i & j => NULL
Si contrainte => pointer vers tuples permis par i & j
=> pointe vers matrice tableau [ valeur ] [ valeur ] (m * m)
Soit 1 ou 0
