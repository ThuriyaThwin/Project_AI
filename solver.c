#include <stdio.h>
#include <mem.h>
#include <malloc.h>

#include "solver.h"

#define IMPOSSIBLE -1
#define VIDE 0
#define AFFECTE 1


int **domainesPrecedents;

void initDomainesPrecedents(int nbPigeons){
    domainesPrecedents = malloc(nbPigeons * sizeof(int));
    for(int i = 0; i < nbPigeons; ++i){
        domainesPrecedents[i] = malloc((nbPigeons - 1) * sizeof(int));
    }

    for(int i = 0; i < nbPigeons; ++i){
        for(int j = 0; j < nbPigeons - 1; ++j){
            domainesPrecedents[i][j] = 0;
            //printf("%d", domaines[i][j]);
        }
        //printf("\n");
    }

}


void printMat(int **domaines, int nbPigeons){
    printf("------------------------\n");
    for(int i = 0; i < nbPigeons; ++i){
        for(int j = 0; j < nbPigeons - 1; ++j){
            printf("%d\t", domaines[i][j]);
        }
        printf("\n");
    }
}

void matricecopy (int **domaines, int nbPigeons) {
    for(int i = 0; i < nbPigeons; ++i){
        for(int j = 0; j < nbPigeons - 1; ++j){
            domainesPrecedents[i][j] = domaines[i][j];
            //printf("%d", domaines[i][j]);
        }
        //printf("\n");
    }
}

void forwardChecking(int **domaines, int nbPigeons){
    initDomainesPrecedents(nbPigeons);
    for(int i = 0; i < nbPigeons; ++i){
        for(int j = 0; j < nbPigeons - 1; ++j){
            printf("----------DOMAINES-----------");
            printMat(domaines, nbPigeons);
            printf("----------DOMAINES PRECEDENTS-----------");
            printMat(domainesPrecedents, nbPigeons);
            if(domaines[i][j] == VIDE) {
                matricecopy(domaines, nbPigeons);
                domaines[i][j] = AFFECTE;
                for(int k = i + 1; k < nbPigeons; ++k){
                    domaines[k][j] = IMPOSSIBLE;
                }
                break;
            }
        }
    }
}