//
// Created by Julien on 16/02/2017.
//

#include "util.h"

int** tuples;

struct CSP {
    int nbVar, nbVal;
    int** domaine;
    int** contraintesTuples;
};
