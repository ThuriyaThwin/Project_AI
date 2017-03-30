#include <stdio.h>

#include "solver.h"

#define IMPOSSIBLE -1
#define VIDE 0
#define AFFECTE 1


int **domainesPrecedents;


void printMat(int **domaines, int nbPigeons){
    printf("------------------------\n");
    for(int i = 0; i < nbPigeons; ++i){
        for(int j = 0; j < nbPigeons - 1; ++j){
            printf("%d", domaines[i][j]);
        }
        printf("\n");
    }
}

void forwardChecking(int **domaines, int nbPigeons){
    for(int i = 0; i < nbPigeons; ++i){
        for(int j = 0; j < nbPigeons - 1; ++j){
            domainesPrecedents = domaines;
            printf("----------------DOMAINE------------");
            printMat(domaines, nbPigeons);
            printf("----------------DOMAINE PRECEDENT------------");
            printMat(domainesPrecedents, nbPigeons);
            if(domaines[i][j] == VIDE) {
                domaines[i][j] = AFFECTE;
                for(int k = i + 1; k < nbPigeons; ++k){
                    domaines[k][j] = IMPOSSIBLE;
                }
                break;
            }
        }
    }
}