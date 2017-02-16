#include <stdio.h>
#include "generator.h"

// Génération pour le problème des pigeons
void pigeonsGenerator(int nbPigeons){
    if( nbPigeons < 0 ){
        fprintf(stderr, "Erreur: nombre de pigeons < 0\n");
        return;
    }

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
}


// Génération pour le problème des dames
void checkersGenerator(unsigned long nbCheckers){

}
