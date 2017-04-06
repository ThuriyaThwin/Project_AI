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

void clearMatrice(int **domaines, int i, int nbPigeons){
    for(int k = i; k < nbPigeons; ++k){
        for (int l = 0; l < nbPigeons -1; ++l) {
            domaines[k][l] = VIDE;
        }
    }
}

void forwardCheckingPigeons(int **domaines, int nbPigeons, int affiche){
    int nbNids = nbPigeons - 1;
    Stack *stack = initStack();

    for(int i = 0; i < nbPigeons; ++i){
        for(int j = 0; j < nbNids; ++j){
            int check = checkForConstraintInCol(domaines, j, nbNids);
            if(check == -1){
                domaines[i][j] = AFFECTE;
                fillColumns(domaines, i+1, j, nbPigeons, IMPOSSIBLE);
                push(stack, domaines, nbPigeons, nbNids);
                if(affiche == 1)
                    printMat(domaines, nbPigeons, nbNids);
                break;
            }
            else{
                if(j == (nbNids -1)){
                    int line = checkForConstraintInCol(domaines, j, nbPigeons) - 1;
                    if(line == -1){
                        printf("Pas de solutions\n");
                        return;
                    }
                    domaines = pop(stack);
                    int col = checkForConstraintInRow(domaines, line, nbNids);
                    clearMatrice(domaines, line, nbPigeons);
                    if(affiche == 1)
                        printMat(domaines, nbPigeons, nbNids);
                    i = line;
                    j = col;
                }
            }
        }
    }
}


void forwardCheckingCheckers(int **domaines, int nbPigeons, int affiche){
    //Stack *stack = initStack();

    for(int i = 0; i < nbPigeons; ++i){
        for(int j = 0; j < nbPigeons; ++j){
            int check = checkForConstraintInCol(domaines, j, nbPigeons);
            int dial = checkForConstraintInDiagonal(domaines, i, j, nbPigeons, nbPigeons);
            if(check == -1 && dial == -1){
                fillColumns(domaines, i+1, j, nbPigeons, IMPOSSIBLE);
                fillDiagonal(domaines, i, j, nbPigeons, IMPOSSIBLE);
                domaines[i][j] = AFFECTE;
                //push(stack, domaines, nbPigeons, nbNids);
                if(affiche == 1)
                    printMat(domaines, nbPigeons, nbPigeons);
                break;
            }
            else{
                if(j == (nbPigeons -1)){
                    int line = checkForConstraintInCol(domaines, j, nbPigeons) - 1;
                    if(line == -1){
                        printf("Pas de solutions\n");
                        return;
                    }
                    else if(line < 0){
                        line = i-1;
                    }
                    //domaines = copyMatrix(pop(stack), nbPigeons, nbNids);
                    int col = checkForConstraintInRow(domaines, line, nbPigeons);
                    if(col == -1)
                        col = 0;
                    clearMatrice(domaines, line, nbPigeons);
                    if(affiche == 1)
                        printMat(domaines, nbPigeons, nbPigeons);
                    i = line;
                    j = col;
                }
            }
        }
    }
}

/*
void forwardCheckingCheckers(int **domaines, int nbCheckers, int affiche){
    int **domaine = copyMatrix(domaines, nbCheckers, nbCheckers);
    Stack *stack = initStack();
    Pile *pile = initPile();

    for(int i = 0; i < nbCheckers; ++i){

        if(domaine[0][nbCheckers-1] == -1){
            printf("Pas de solution");
            exit(0);
        }

        for(int j = 0; j < nbCheckers; ++j){
            int check = checkForConstraintInCol(domaine, j, nbCheckers);
            int dial = checkForConstraintInDiagonal(domaine, i, j, nbCheckers, nbCheckers);
            if(check == -1 && dial == -1){
                if(domaine[i][j] == -1) continue;
                fillColumns(domaine, i+1, j, nbCheckers, IMPOSSIBLE);
                fillDiagonal(domaine, i, j, nbCheckers, IMPOSSIBLE);
                domaine[i][j] = AFFECTE;
                if(affiche == 1)
                    printMat(domaine, nbCheckers, nbCheckers);
                push(stack, domaine, nbCheckers, nbCheckers);
                pushPile(pile, j);
                break;
            }
            else{
                if(j == (nbCheckers -1)){
                    int line = checkForConstraintInCol(domaine, j, nbCheckers) - 1;
                    if(line == -1){
                        printf("Pas de solutions\n");
                        return;
                    }
                    //printf("Coords : %d,%d\n", i, j);
                    int test = popPile(pile);
                    domaine = pop(stack);
                    --i;
                    if(domaine[i][j] == IMPOSSIBLE) {
                        --i;
                        if (i == 0) {
                            domaine = copyMatrix(domaines, nbCheckers, nbCheckers);
                        }
                        break;
                    }


                    domaine[i][test] = IMPOSSIBLE;
                    fillColumns(domaine, i + 1, test, nbCheckers, VIDE);
                    fillDiagonal(domaine, i + 1, test, nbCheckers, VIDE);
                    //printf("%d,%d\n", i, test);
                    printMat(domaine, nbCheckers, nbCheckers);

                    j = 0;
                    //printf("%d, %d", i, j);


                        //int col = checkForConstraintInRow(domaine, line, nbCheckers);
                    //if(affiche == 1)
                    //    printMat(domaine, nbCheckers);
                    //i = line;
                    //j = col;
                }
            }
        }
    }
}

void forwardCheckingCheckersUneSolution(int **domaines, int nbCheckers, int affiche){
    int **domaine = copyMatrix(domaines, nbCheckers, nbCheckers);
    Stack *stack = initStack();
    Pile *pile = initPile();

    for(int i = 0; i < nbCheckers; ++i){

        if(domaine[0][nbCheckers-1] == -1){
            printf("Pas de solution");
            exit(0);
        }

        for(int j = 0; j < nbCheckers; ++j){
            int check = checkForConstraintInCol(domaine, j, nbCheckers);
            int dial = checkForConstraintInDiagonal(domaine, i, j, nbCheckers, nbCheckers);
            if(check == -1 && dial == -1){
                if(domaine[i][j] == -1) continue;
                fillColumns(domaine, i+1, j, nbCheckers, IMPOSSIBLE);
                fillDiagonal(domaine, i, j, nbCheckers, IMPOSSIBLE);
                domaine[i][j] = AFFECTE;
                if(affiche == 1)
                    printMat(domaine, nbCheckers, nbCheckers);
                push(stack, domaine, nbCheckers, nbCheckers);
                pushPile(pile, j);
                break;
            }
            else{
                if(j == (nbCheckers -1)){
                    int line = checkForConstraintInCol(domaine, j, nbCheckers) - 1;
                    if(line == -1){
                        printf("Pas de solutions\n");
                        return;
                    }
                    //printf("Coords : %d,%d\n", i, j);
                    int test = popPile(pile);
                    domaine = pop(stack);
                    --i;
                    if(domaine[i][j] == IMPOSSIBLE) {
                        --i;
                        if (i == 0) {
                            domaine = copyMatrix(domaines, nbCheckers, nbCheckers);
                        }
                        break;
                    }


                    domaine[i][test] = IMPOSSIBLE;
                    fillColumns(domaine, i + 1, test, nbCheckers, VIDE);
                    fillDiagonal(domaine, i + 1, test, nbCheckers, VIDE);
                    //printf("%d,%d\n", i, test);
                    printMat(domaine, nbCheckers, nbCheckers);

                    j = 0;
                    //printf("%d, %d", i, j);


                    //int col = checkForConstraintInRow(domaine, line, nbCheckers);
                    //if(affiche == 1)
                    //    printMat(domaine, nbCheckers);
                    //i = line;
                    //j = col;
                }
            }
        }
    }
}
*/