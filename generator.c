#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

// Génération pour le problème des pigeons
void pigeonsGenerator(int nbPigeons){
    if( nbPigeons < 0 ){
        fprintf(stderr, "Erreur: nombre de pigeons < 0\n");
        return;
    }


    printf("%d \n", nbPigeons);

    FILE* txt;

    txt = fopen("pigeon.txt", "w");

    fprintf(txt, "TEST\n");



    fclose(txt);
}


// Génération pour le problème des dames
void checkersGenerator(unsigned long nbCheckers){

}
