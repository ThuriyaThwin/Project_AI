#include <stdio.h>
#include <stdlib.h>

#include "pigeon.h"
#include "matrix.h"

// GENERATION INITIALIE POUR LES PIGEONS
// Ecriture dans le fichier + création du CSP
CSP* pigeonGenerator(int nbPigeon, int nbNest, int writeTXT){

    CSP* newCSP = initCSP(nbPigeon, nbNest);

    int** matrixCouple = createNewMatrix(nbNest, nbNest);
    for(int i=0; i < nbNest; ++i){
        for(int j=0; j < nbNest; ++j){
            if( i != j ){
                matrixCouple[i][j] = 1;
            }
        }
    }


    FILE* txt = fopen("config_pigeon.txt", "w");

    if(writeTXT){

        // Ligne variable X
        fprintf(txt, "X\n");
        for(int i=0; i < nbPigeon; ++i)
            fprintf(txt, "%d ", i);
        fprintf(txt, "\n");

    }

    if(writeTXT){

        //Lignes domaines D
        fprintf(txt, "D\n");
        for(int i=0; i < nbPigeon; ++i){
            fprintf(txt, "d%d = ", i);
            for(int j=0; j < nbNest; ++j)
                fprintf(txt, "%d ", j);
            fprintf(txt, "\n");
        }

    }


    //Lignes contraintes C
    if(writeTXT) fprintf(txt, "C\n");

    for(int i=0; i < nbPigeon; ++i){
        for(int j=i+1; j < nbPigeon; ++j){
            if(i == j) continue;

            if(writeTXT) fprintf(txt, "(%d, %d) & (%d, %d)\n", i, j, j, i);

            //Lignes tuples permis
            newCSP->matrixConstraint[i][j] = matrixCouple;//createNewMatrix(nbNest, nbNest);
            newCSP->matrixConstraint[j][i] = matrixCouple;//createNewMatrix(nbNest, nbNest);

            if(writeTXT){
                for(int k = 0; k < nbNest; ++k)
                    for(int l = 0; l < nbNest; ++l) {
                        if(k == l) continue;

                         fprintf(txt, "%d %d\n", k, l);

                        //newCSP->matrixConstraint[i][j][k][l] = 1;
                        //newCSP->matrixConstraint[j][i][k][l] = 1;
                    }
            }
        }
    }

    fclose( txt );

    return newCSP;
}
