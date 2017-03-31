#include <stdio.h>
#include <stdlib.h>
#include "util.c"

int main(int argc, char** argv){
    if( argc != 2 ){
        printf("erreur arguments\n");
        exit(-1);
    }

    int i, j;
    int** domaines;
    int** domaines_init;
    int nbPigeons = atoi(argv[1]);

    printf("Démarrage avec %d pigeons & %d nids.\n", nbPigeons, (nbPigeons-1));

    // Initialisation d'une matrice
    domaines = createNewMatrice(nbPigeons, nbPigeons-1);
    domaines_init = copyMatrice(domaines, nbPigeons, nbPigeons-1);

    printf("Matrice init :\n");
    printMatrice(domaines, nbPigeons, nbPigeons-1);

    printf("Matrice copy init :\n");
    printMatrice(domaines_init, nbPigeons, nbPigeons-1);

    for(i=0; i < nbPigeons; ++i){
        free(domaines[i]);
        free(domaines_init[i]);
    }

    free( domaines );
    free( domaines_init );

    return 0;
}
