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

#endif //PROJET_IA_UTIL_H
