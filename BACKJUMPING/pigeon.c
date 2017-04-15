#include <stdio.h>
#include <stdlib.h>

#include "pigeon.h"

// GENERATION INITIALIE POUR LES PIGEONS
// Ecriture dans le fichier + création du CSP
CSP* pigeonGenerator(int nbPigeon, int nbNest){

    CSP* newCSP = initCSP(nbPigeon, nbNest);
    char buffer[999999];

    // Ligne variable X
    sprintf(buffer, "X\n");
    for(int i=0; i < nbPigeon; ++i)
        sprintf(buffer, "%s%d ", buffer, i);
    sprintf(buffer,"%s\n", buffer);

    //Lignes domaines D
    sprintf(buffer, "%sD\n", buffer);
    for(int i=0; i < nbPigeon; ++i){
        sprintf(buffer, "%sd%d = ", buffer, i);
        for(int j=0; j < nbNest; ++j)
            sprintf(buffer, "%s%d ", buffer, j);
        sprintf(buffer,"%s\n", buffer);
    }

    //Lignes contraintes C
    sprintf(buffer, "%sC\n", buffer);
    for(int i=0; i < nbPigeon; ++i){
        for(int j= i+1; j < nbPigeon; ++j){
            if(i == j) continue;
            sprintf(buffer, "%s(%d, %d)\n", buffer, i , j);

            //Lignes tuples permis
            for(int k = 0; k < nbNest; ++k)
                for(int l = 0; l < nbNest; ++l) {
                    if(k == l) continue;
                    sprintf(buffer, "%s%d %d\n", buffer, k, l);
                }
        }
    }

    FILE* txt = fopen("config_pigeon.txt", "w");
    fputs(buffer, txt);
    fclose( txt );

    return newCSP;
}
