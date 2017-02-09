#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

// Génération pour le problème des pigeons
void pigeonsGenerator(int nbPigeons){
    if( nbPigeons < 0 ){
        fprintf(stderr, "Erreur: nombre de pigeons < 0\n");
        return;
    }

    printf("Nombre de pigeons selectiones : %d \n", nbPigeons);

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

    for(int i=0; i < nbPigeons-1; ++i){
        for(int j=(i+1); j < nbPigeons; ++j){
            fprintf(txt, "%d.nid != %d.nid\n", i, j);
        }
    }

    fclose(txt);
}


// Génération pour le problème des dames
void checkersGenerator(unsigned long nbCheckers){

}
