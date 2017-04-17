#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "solver.h"

#define IMPOSSIBLE -1
#define VIDE 0
#define AFFECTE 1

void printMat(int **domaines, int nbPigeons, int nbNids){
    printf("----------DOMAINES-----------\n");
    for(int i = 0; i < nbPigeons; ++i){
        for(int j = 0; j < nbNids; ++j){
            printf("%d\t", domaines[i][j]);
        }
        printf("\n");
    }
}

void forwardCheckingPigeons(int **domaine, int nbPigeons, int affiche){
    int nbNids = nbPigeons - 1;
    Stack *stack = initStack();

    for(int i = 0; i < nbPigeons; ){
        for(int j = 0; j < nbNids; ){
            if(affiche == 1)
                printMat(domaine, nbPigeons, nbNids);
            if(domaine[i][j] == VIDE){
                push(stack, domaine, nbPigeons, nbNids);
                domaine[i][j] = AFFECTE;
                fillColumns(domaine, i, j, nbPigeons, IMPOSSIBLE);
                ++i;
                j = 0;
            }
            else {
                if((domaine[i][j] == IMPOSSIBLE) && (j == nbNids - 1)){
                    if(i == 0)
                        return;
                    --i;
                    int index = checkForConstraintInRow(domaine, i, nbNids);
                    domaine = pop(stack);
                    domaine[i][index] = IMPOSSIBLE;
                    j = 0;
                }
                else{
                    ++j;
                }
            }
        }
    }

}

