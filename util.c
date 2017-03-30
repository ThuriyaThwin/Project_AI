//
// Created by Julien on 16/02/2017.
//

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "util.h"


int** copyMatrice(int** matriceSource, int lengthDimOne, int lengthDimTwo){
    int** newMatrice;

    newMatrice = malloc( lengthDimOne * sizeof(int*));
    for(int i = 0; i < lengthDimOne; ++i){
        newMatrice[i] = malloc( lengthDimTwo * sizeof(int) );
    }

    for(int i=0; i < lengthDimOne; ++i){
        for(int j=0; j < lengthDimTwo; ++j){
            newMatrice[i][j] = matriceSource[i][j];
        }
    }

    return newMatrice;
}

int **depiler(Pile *pile) {
    if (pile == NULL)
        exit(EXIT_FAILURE);

    int **domaine = 0;
    Element *elementDepile = pile->premier;

    if (pile->premier != NULL) {
        domaine = elementDepile->domaine;
        pile->premier = elementDepile->suivant;
        free(elementDepile);
    }
    return domaine;
}

void empiler(Pile *pile, int **domaines) {
    Element *nouveau = malloc(sizeof(*nouveau));
    if (pile == NULL || nouveau == NULL)
        exit(EXIT_FAILURE);

    nouveau->domaine = domaines;
    nouveau->suivant = pile->premier;
    pile->premier = nouveau;
}

Coords findLastModif(int **domaines, int nbPigeons){
    Coords coords;
    coords.x = -1;
    coords.y = -1;
    for(int i = 0; i < nbPigeons; ++i){
        for(int j = 0; j < nbPigeons - 1; ++j){
            if(domaines[i][j] == 1){
                coords.x = i;
                coords.y = j;
            }
        }
    }
    return coords;
}

void fillColumns(int **domaines, int i, int j, int nbPigeons, int value){
    for(int k = i; k < nbPigeons; ++k)
        domaines[k][j] = value;
}
