#include <stdio.h>
#include <stdlib.h>
#include "util.c"

int main(int argc, char** argv){
    if( argc != 2 ){
        printf("erreur arguments\n");
        exit(-1);
    }

    int i, j;
    int **domaines;
    int nbPigeons = atoi(argv[1]);

    printf("Démarrage avec %d pigeons & %d nids.\n", nbPigeons, (nbPigeons-1));
    printf("MATRICE DOMAINE :\n");


    domaines = malloc(nbPigeons * sizeof(int*));
    for(i = 0; i < nbPigeons; ++i){
        domaines[i] = malloc( (nbPigeons - 1) * sizeof(int) );
    }

    for(i = 0; i < nbPigeons; ++i){
        for(j = 0; j < nbPigeons - 1; ++j){
            domaines[i][j] = 0;
            printf("%d", domaines[i][j]);
        }
        printf("\n");
    }





    int** domaines_init = copyMatrice(domaines, nbPigeons);
    printf("%d\n", domaines_init[0][0]);

    for(i=0; i < nbPigeons; ++i){ free(domaines[i]); }
    free( domaines );

    return 0;
}
