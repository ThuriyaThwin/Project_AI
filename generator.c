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

    struct CSP pigeon;

    pigeon.domaine = malloc( nbPigeons * sizeof( *pigeon.domaine ) );
    if( pigeon.domaine == NULL) return;

    for(int i=0; i < nbPigeons; ++i){
        pigeon.domaine[i] = malloc( (nbPigeons-1) * sizeof( **pigeon.domaine ) );
        if( pigeon.domaine[i] == NULL ) return;
    }

    pigeon.domaine[0][0] = 1;

    printf("--> %d\n", pigeon.domaine[0][0] );
    printf(" çç %d\n", pigeon.domaine[nbPigeons-1][nbPigeons-2] );


    printf("Nombre de pigeons : %d \n", nbPigeons);

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


    for(int i=0; i < nbPigeons-1; ++i)
        free( pigeon.domaine[i] );

    free( pigeon.domaine );
}


// Génération pour le problème des dames
void checkersGenerator(unsigned long nbCheckers){

}
