#include <stdio.h>
#include <stdlib.h>
#include "generator.h"
#include "util.c"

// Génération pour le problème des pigeons
void pigeonsGenerator(int nbPigeons){
    if( nbPigeons < 0 ){
        fprintf(stderr, "Erreur: nombre de pigeons < 0\n");
        return;
    }

    printf("Nombre de pigeons : %d \n", nbPigeons);

    struct CSP pigeon;
    int nbNests = nbPigeons-1;

    // DOMAINES :
    pigeon.domaine = malloc( nbPigeons * sizeof( int* ) );
    if( pigeon.domaine == NULL) return;

    for(int i=0; i < nbPigeons; ++i){
        pigeon.domaine[i] = malloc( nbNests * sizeof( int ) );
        if( pigeon.domaine[i] == NULL ) return;
    }


    // TUPLES :
    struct contrainte contraintes;
    contraintes.tuples = malloc( nbNests * sizeof( int* ) );
    if( contraintes.tuples == NULL ) return;

    for(int i=0; i < nbNests; ++i){
        contraintes.tuples[i] = malloc( nbNests * sizeof( int ) );
        if( contraintes.tuples[i] == NULL ) return;
    }


    // CONTRAINTES :
    pigeon.contraintes = malloc( nbPigeons * sizeof( int* ) );
    if( pigeon.contraintes == NULL ) return;

    for(int i=0; i < nbPigeons; ++i){
        pigeon.contraintes[i] = NULL;
    }

    printf("taille : %d - %d\n", nbPigeons, nbNests);

    for(int i=0; i < nbPigeons; i++)
        for(int j=0; j < nbNests; j++)
            pigeon.domaine[i][j] = 1;

    for(int i=0; i < nbPigeons; ++i){
        for(int j=0; j < nbNests; j++){
            printf("[%d][%d] = %d\n", i, j, pigeon.domaine[i][j]);
        }
    }

    // Création d'un nouveau fichier de configuration pour les pigeons
    FILE* txt;
    txt = fopen("config_pigeon.txt", "w");
    // Ligne variable X
    fprintf(txt, "X\n");
    for(int i=0; i < nbPigeons; ++i)
        fprintf(txt, "%d ", i);
    fprintf(txt,"\n");

    //Lignes domaines D
    fprintf(txt, "D\n");
    for(int i=0; i < (nbPigeons); ++i){

        fprintf(txt, "d%d = ", i);
        for(int j=0; j < (nbPigeons-1); ++j)
            fprintf(txt, "%d ", j);
        fprintf(txt,"\n");

    }

    //Lignes contraintes C
    fprintf(txt, "C\n");

    for(int i=0; i < nbPigeons; ++i){
        for(int j= i+1; j < nbPigeons; ++j){
            if(i == j) continue;
            fprintf(txt, "(%d, %d)\n", i , j);

            for(int k = 0; k < nbPigeons - 1; ++k)
                for(int l = 0; l < nbPigeons - 1; ++l) {
                    if(k == l) continue;
                    fprintf(txt, "%d %d\n", k, l);
                }
        }
    }

    fclose(txt);

    for(int i=0; i < nbPigeons; ++i){
        free( pigeon.domaine[i] );
        free( pigeon.contraintes[i] );
    }

    for(int i=0; i < nbNests; ++i){
        free( contraintes.tuples[i] );
    }

    free( pigeon.domaine );
    free( pigeon.contraintes );
    free( contraintes.tuples );
}


// Génération pour le problème des dames
void checkersGenerator(unsigned long nbCheckers){

}
