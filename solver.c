#include <stdio.h>
#include <malloc.h>
#include "util.h"
#include "solver.h"

#define IMPOSSIBLE -1
#define VIDE 0
#define AFFECTE 1

int **domainesPrecedents;

void initDomainesPrecedents(int nbPigeons){
    domainesPrecedents = malloc(nbPigeons * sizeof(int));
    for(int i = 0; i < nbPigeons; ++i)
        domainesPrecedents[i] = malloc((nbPigeons - 1) * sizeof(int));

    for(int i = 0; i < nbPigeons; ++i)
        for(int j = 0; j < nbPigeons - 1; ++j)
            domainesPrecedents[i][j] = 0;
}

void printMat(int **domaines, int nbPigeons){
    printf("----------DOMAINES-----------\n");
    for(int i = 0; i < nbPigeons; ++i){
        for(int j = 0; j < nbPigeons - 1; ++j){
            printf("%d\t", domaines[i][j]);
        }
        printf("\n");
    }
}

/*void matricecopy (int **domaines, int nbPigeons) {
    for(int i = 0; i < nbPigeons; ++i){
        for(int j = 0; j < nbPigeons - 1; ++j){
            domainesPrecedents[i][j] = domaines[i][j];
            //printf("%d", domaines[i][j]);
        }
        //printf("\n");
    }
}*/

void forwardChecking(int **domaines, int nbPigeons){
    initDomainesPrecedents(nbPigeons);
    for(int i = 0; i < nbPigeons; ++i){
        for(int j = 0; j < nbPigeons - 1; ++j){
            printMat(domaines, nbPigeons);
            while (domaines[i][j] == IMPOSSIBLE && j == (nbPigeons - 2)){
                --i;
                if(domaines[i][j] == AFFECTE){
                    fillColumns(domaines, i, j, nbPigeons, VIDE);
                    --i;
                    --j;
                    fillColumns(domaines, i, j, nbPigeons, VIDE);
                    printMat(domaines, nbPigeons);
                    printf("i = %d, j = %d", i, j);
                    ++j;
                }
            }
            if(domaines[i][j] == VIDE) {
                //matricecopy(domaines, nbPigeons);
                domaines[i][j] = AFFECTE;
                fillColumns(domaines, i + 1, j, nbPigeons, IMPOSSIBLE);
                break;
            }
        }
    }

    /*int x = findLastModif(domainesPrecedents, nbPigeons).x;
    int y = findLastModif(domainesPrecedents, nbPigeons).y;
    printf("Last 1 : x = %d, y = %d", x, y);*/
}