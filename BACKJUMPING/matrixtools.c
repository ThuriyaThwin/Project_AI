#include <stdio.h>
#include <stdlib.h>
#include "matrixtools.h"

// Création d'un tableau d'entier à nbElement
int* newTab(int nbElement){ return malloc( nbElement * sizeof(int) ); }

// Création d'une matrice à lenDimOne * lenDimTwo éléments
int** newMatrix(int lenDimOne, int lenDimTwo){
    int** newMatrix = malloc( lenDimOne * sizeof(int*) );

    for(int i=0; i < lenDimOne; ++i)
        newMatrix[i] = newTab(lenDimTwo);

    return newMatrix;
}

// Libération de mémoire d'une matrice
void freeMatrix(int** matrix, int lenDimOne){
    for(int i=0; i < lenDimOne; ++i)
        free( matrix[i] );
    free( matrix );
}

void printTab(int* tab, int nbElement){
    for(int i=0; i < nbElement; ++i)
        printf("[%d]", tab[i]);
    printf("\n");
}

void printMatrix(int** matrix, int lenDimOne, int lenDimTwo){
    for(int i=0; i < lenDimOne; ++i)
        printTab(matrix[i], lenDimTwo);
}
