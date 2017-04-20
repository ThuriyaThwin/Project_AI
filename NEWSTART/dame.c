#include <stdio.h>
#include <stdlib.h>

#include "dame.h"
#include "matrix.h"

CSP* dameGenerator(int nbDame, int writeTXT){

    CSP* newCSP = initCSP(nbDame, nbDame);

    int** matrixCouple = createNewMatrix(nbDame, nbDame);
    for(int i=0; i < nbDame; ++i){
        for(int j=0; j < nbDame; ++j){
            if( i != j ){


                matrixCouple[i][j] = 1;


            }
        }
    }

    FILE* txt = fopen("config_dame.txt", "w");

    if(writeTXT){
        // Ligne variable X
        fprintf(txt, "X\n");
        for(int i=0; i < nbDame; ++i)
            fprintf(txt, "%d ", i);
        fprintf(txt, "\n");
    }

    if(writeTXT){
        //Lignes domaines D
        fprintf(txt, "D\n");
        for(int i=0; i < nbDame; ++i){
            fprintf(txt, "d%d = ", i);
            for(int j=0; j < nbDame; ++j)
                fprintf(txt, "%d ", j);
            fprintf(txt, "\n");
        }
    }


    //Lignes contraintes C
    if(writeTXT) fprintf(txt, "C\n");
    for(int i=0; i < nbDame; ++i){
        for(int j=i+1; j < nbDame; ++j){
            if(i == j) continue;

            if(writeTXT) fprintf(txt, "(%d, %d) & (%d, %d)\n", i, j, j, i);

            //Lignes tuples permis
            newCSP->matrixConstraint[i][j] = matrixCouple;
            newCSP->matrixConstraint[j][i] = matrixCouple;

            if(writeTXT){
                for(int k = 0; k < nbDame; ++k)
                    for(int l = 0; l < nbDame; ++l) {
                        if(k == l) continue;
                         fprintf(txt, "%d %d\n", k, l);
                    }
            }
        }
    }


    fclose( txt );

    return newCSP;
}
