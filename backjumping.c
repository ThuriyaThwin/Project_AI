#include <stdio.h>
#include <stdlib.h>
#include "util.c"

int main(int argc, char** argv){
    if( argc != 2 ){
        printf("erreur arguments\n");
        exit(-1);
    }

    int i;
    int** domaines;
    int nbPigeons = atoi(argv[1]);
    int nbNids = (nbPigeons-1);

    Stack* stack = initStack();
    printf("Démarrage avec %d pigeons & %d nids.\n", nbPigeons, nbNids);

    // Initialisation d'une matrice
    domaines = createNewMatrix(nbPigeons, nbNids);
    push(stack, domaines, nbPigeons, nbNids);
    printMatrix(stack->top->matrix, nbPigeons, nbNids);

    for(i=0; i < nbPigeons; ++i){
        free(domaines[i]);
    }

    free( domaines );

    wipeStack(stack, nbPigeons);

    return 0;
}
