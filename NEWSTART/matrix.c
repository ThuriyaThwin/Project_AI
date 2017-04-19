#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

// Création d'un tableau d'entier à nbElement
int* createNewTab(int nbElement){ return malloc( nbElement * sizeof(int) ); }

// Création d'une matrice à lenDimOne * lenDimTwo éléments
int** createNewMatrix(int lenDimOne, int lenDimTwo){
    int** newMatrix = malloc( lenDimOne * sizeof(int*) );

    for(int i=0; i < lenDimOne; ++i)
        newMatrix[i] = createNewTab(lenDimTwo);

    return newMatrix;
}

// Libération de mémoire d'une matrice
void freeMatrix(int** matrix, int lenDimOne){
    for(int i=0; i < lenDimOne; ++i){
        if( matrix[i] != NULL )
            free( matrix[i] );
    }
    if( matrix != NULL)
        free( matrix );
}

// Copier un tableau par valeur
int* copyTab(int* tab, int nbElement){
    int* newTab = createNewTab(nbElement);
    for(int i=0; i < nbElement; ++i){
        newTab[i] = tab[i];
    }

    return newTab;
}

// Copie par valeur d'une matice row*col vers une nouvelle row*col
int** copyMatrix(int** sourceMatrix, int row, int col){
    int** newMatrix;
    newMatrix = createNewMatrix(row, col);
    for(int i=0; i < row; ++i){
        for(int j=0; j < col; ++j){
            newMatrix[i][j] = sourceMatrix[i][j];
        }
    }

    return newMatrix;
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
