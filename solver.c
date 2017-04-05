#include <stdio.h>
#include <malloc.h>
#include "util.h"
#include "solver.h"

#define IMPOSSIBLE -1
#define VIDE 0
#define AFFECTE 1

void printMat(int **domaines, int nbPigeons){
    printf("----------DOMAINES-----------\n");
    for(int i = 0; i < nbPigeons; ++i){
        for(int j = 0; j < nbPigeons - 1; ++j){
            printf("%d\t", domaines[i][j]);
        }
        printf("\n");
    }
}

void clearMatrice(int **domaines, int i,int j, int nbPigeons){
    for(int k = i; k < nbPigeons; ++k){
        for (int l = j; l < nbPigeons -1; ++l) {
            domaines[k][l] = VIDE;
        }
    }
}

void forwardChecking(int **domaines, int nbPigeons){
    printf("nb p : %d", nbPigeons);
    int nbNids = nbPigeons - 1;

    for(int i = 0; i < nbPigeons; ++i){
        for(int j = 0; j < nbNids; ++j){
            int check = checkForConstraintInCol(domaines, j, nbNids);
            if(check == -1){
                domaines[i][j] = AFFECTE;
                fillColumns(domaines, i, j, nbPigeons, IMPOSSIBLE);
                printMat(domaines, nbPigeons);
                break;
            }
            else{
                if(j == (nbNids -1)){
                    int line = checkForConstraintInCol(domaines, j, nbPigeons) - 1;
                    if(line == -1){
                        printf("Pas de solutions\n");
                        return;
                    }
                    int col = checkForConstraintInRow(domaines, line, nbNids);
                    clearMatrice(domaines, line, col, nbPigeons);
                    printMat(domaines, nbPigeons);
                    i = line;
                    j = col;
                }
            }
        }
    }

}