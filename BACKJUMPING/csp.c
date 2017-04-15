#include <stdio.h>
#include <stdlib.h>

#include "csp.h"
#include "matrixtools.h"

/*
    @param : nombre de variable dans notre problème
    @param : nombre de valeur que peuvent prendre nos variables
    @return : une structure CSP contenant nos matrices initialisés
*/

CSP* initCSP(int nbVariable, int nbValue){
    // Allocation de notre structure CSP
    CSP* newCSP = malloc(sizeof( *newCSP ));

    int** mat = newMatrix(2, 2);
    mat[0][0] = 0;
    mat[0][1] = 1;
    mat[1][0] = 1;
    mat[1][1] = 0;

    // Allocation des différentes matrices contenues dans notre CSP
    newCSP->matrixConstraint = malloc( nbVariable * sizeof(int**) );
    for(int i=0; i < nbVariable; ++i){
        newCSP->matrixConstraint[i] = malloc( nbVariable * sizeof(int*) );

        for(int j=0; j < nbVariable; ++j){
            newCSP->matrixConstraint[i][j] = NULL ; // Fonctionne
            newCSP->matrixConstraint[i][j] = *mat ; // Fonctionne

            // AFFICHAGE DEBUG :
            printf("{\n");
            for(int k=0; k < 2; ++k){
                for(int l=0; l < 2; ++l){
                    printf("[%d]", *(newCSP->matrixConstraint[i][j]) + k*2 + l );
                }
                printf("\n");
            }
            printf("}\n");
            // FONCTIONNE

        }
    }


    newCSP->matrixDomain = newMatrix(nbVariable, nbValue);

    return newCSP;
}

/*
    Libération de mémoire pour le CSP
*/
void freeCSP(CSP* csp, int nbVariable, int nbValue){

    // Libération de la mémoire allouée pour les matrices
    //freeMatrix(csp->matrixConstraint, nbVariable);
    freeMatrix(csp->matrixDomain, nbVariable);


    /*for(int i=0; i < nbVariable; ++i){

        free( csp->matrixConstraint);

    }*/


    // Libération de mémoire pour la structure CSP
    free( csp );
}

/*
    AFFICHAGE CSP :
*/
void printCSP(CSP* csp, int nbVariable, int nbValue){
    printf("\n\n----| CSP |----\n");
    printf("\n+++ CONTRAINTES +++\n");
    //printMatrix(csp->matrixConstraint, nbVariable, nbVariable);
    printf("\n--- DOMAINE ---\n");
    printMatrix(csp->matrixDomain, nbVariable, nbValue);
    //printf("\n+++ TUPLES +++\n");
    //

    // //*(arrayP[i][0]) + k*2 + l ) <<<<--- Pour accéder à une valeur


    printf("\n----| FIN |----\n");
}
