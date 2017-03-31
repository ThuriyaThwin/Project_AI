#include <stdio.h>
#include <stdlib.h>
#include "util.c"

int main(int argc, char** argv){
    if( argc != 2 ){
        printf("erreur arguments\n");
        exit(-1);
    }

    int i;
    int** domaineInit;
    int nbPigeons = atoi(argv[1]);
    int nbNids = (nbPigeons-1);


    printf("Démarrage avec %d pigeons & %d nids.\n", nbPigeons, nbNids);

    // Initialisation d'une matrice
    domaineInit = createNewMatrix(nbPigeons, nbNids);

    // Initialisation de la pile de matrice
    Stack* stack = initStack();

    domaineInit[0][0] = 1;

    printMatrix(domaineInit, nbPigeons, nbNids);









    printAllStack(stack, nbPigeons, nbNids);
    //printMatrix(stack->top->matrix, nbPigeons, nbNids);


    wipeStack(stack, nbPigeons);

    for(i=0; i < nbPigeons; ++i){
        free(domaineInit[i]);
    }
    free( domaineInit );



    return 0;
}
