//
// Created by Julien on 16/02/2017.
//

#include "util.h"

typedef struct contrainte {
    int** tuples;
} contrainte;

struct CSP {
    int nbVar, nbVal;
    int** domaine;
    contrainte** contraintes;
};
