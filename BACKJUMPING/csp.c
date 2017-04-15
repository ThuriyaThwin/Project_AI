#include <stdio.h>
#include <stdlib.h>

#include "csp.h"

/*
    @param : nombre de variable dans notre problème
    @param : nombre de valeur que peuvent prendre nos variables
    @return : une structure CSP contenant nos matrices initialisés
*/

CSP* initCSP(int nbVariable, int nbValue){
    // Allocation de notre structure CSP
    CSP* newCSP = malloc(sizeof( *newCSP ));

    // Allocation Contraintes
    newCSP->matrixConstraint = newConstraintMatrix(nbVariable);

    // Allocation Domaines
    newCSP->matrixDomain = newMatrix(nbVariable, nbValue);

    return newCSP;
}

/*
    Libération de mémoire pour le CSP
*/
void freeCSP(CSP* csp, int nbVariable, int nbValue){

    // Libération de la mémoire allouée pour les matrices
    freeMatrix(csp->matrixDomain, nbVariable);
    freeConstraintMatrix(csp->matrixConstraint, nbVariable, nbValue);

    // Libération de mémoire pour la structure CSP
    free( csp );
}

/*
    AFFICHAGE CSP :
*/
void printCSP(CSP* csp, int nbVariable, int nbValue){
    printf("\n\n----| CSP |----\n");
    printf("\n+++ CONTRAINTES & TUPLES +++\n");

    for(int i=0; i < nbVariable; ++i){
        for(int j=0; j < nbVariable; ++j){
            if( csp->matrixConstraint[i][j] != NULL ){
                printf(">>> CONTRAINTE (%d,%d) <<<\n", i, j);
                printMatrix(csp->matrixConstraint[i][j], nbValue, nbValue);
            }
        }
    }

    printf("\n+++ DOMAINE +++\n");
    printMatrix(csp->matrixDomain, nbVariable, nbValue);

    printf("\n----| FIN |----\n");
}


/*    MATRICE       */
/*
 Création de la matrice de contrainte, toutes les contraintes sont initialisés à NULL.
 Ce sera aux différents générateurs de remplir les tuples de ces fameuses contraintes.
*/
int**** newConstraintMatrix(int nbElement){
    int**** matrixConstraint = malloc( nbElement * sizeof(int***) );
    for(int i=0; i < nbElement; ++i){
        matrixConstraint[i] = malloc( nbElement * sizeof(int**) );
        for(int j=0; j < nbElement; ++j)
            matrixConstraint[i][j] = NULL;
    }

    return matrixConstraint;
}

// Création d'un tableau d'entier à nbElement
int* newTab(int nbElement){ return malloc( nbElement * sizeof(int) ); }

// Création d'une matrice à lenDimOne * lenDimTwo éléments
int** newMatrix(int lenDimOne, int lenDimTwo){
    int** newMatrix = malloc( lenDimOne * sizeof(int*) );

    for(int i=0; i < lenDimOne; ++i)
        newMatrix[i] = newTab(lenDimTwo);

    return newMatrix;
}


void freeConstraintMatrix(int**** matrix, int nbConstraintElement, int nbTupleElement){
    for(int i=0; i < nbConstraintElement; ++i){
        for(int j=0; j < nbConstraintElement; ++j)
            if( matrix[i][j] != NULL )
                freeMatrix(matrix[i][j], nbTupleElement);

        free( matrix[i] );
    }
    free( matrix );
}


// Libération de mémoire d'une matrice
void freeMatrix(int** matrix, int lenDimOne){
    for(int i=0; i < lenDimOne; ++i)
        free( matrix[i] );
    free( matrix );
}

// Afficher un tableau de nbElement
void printTab(int* tab, int nbElement){
    for(int i=0; i < nbElement; ++i)
        printf("[%d]", tab[i]);
    printf("\n");
}

// Afficher une matrice
void printMatrix(int** matrix, int lenDimOne, int lenDimTwo){
    for(int i=0; i < lenDimOne; ++i)
        printTab(matrix[i], lenDimTwo);
}
