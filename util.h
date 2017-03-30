//
// Created by Julien on 16/02/2017.
//

#ifndef PROJET_IA_UTIL_H
#define PROJET_IA_UTIL_H

typedef struct Element Element;
struct Element {
    int **domaine;
    Element *suivant;
};

typedef struct Pile Pile;
struct Pile {
    Element *premier;
};

typedef struct Coords Coords;
struct Coords{
    int x;
    int y;
};

struct Coords findLastModif(int **domaines, int nbPigeons);

void fillColumns(int **domaines, int i, int j, int nbPigeons, int value);

#endif //PROJET_IA_UTIL_H
