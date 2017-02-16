//
// Created by Julien on 16/02/2017.
//

#include "util.h"

struct CSP{
    int nbVar, nbVal;

    int domaine[nbVar][nbVal]; //[pigeon][nid possible]

    struct contraintes contrainte[nbVar][nbVar]; //null ou 1
};


struct contraintes{
    int nbVal;
    int tuple[nbVal][nbVal];
};