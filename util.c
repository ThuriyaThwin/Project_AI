//
// Created by Julien on 16/02/2017.
//

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "util.h"

/*
    GESTION PILE
*/
// Fonction d'initialisation de la Pile
Stack* initStack(){
    Stack* stack = malloc(sizeof( *stack ));
    stack->top = NULL;

    return stack;
}

// Ajout d'une sauvegarde de matrice dans la Pile
// IMPORTANT : Copie par Valeur faite automatiquement lors du push (on duplique la matrice actuelle | 2 pointeurs)
//                          ^-----> void createNewMatrice(int** matrix);
void push(Stack* stack, int** matrix, int row, int col){
    Node* newTop = malloc(sizeof( *newTop ));
    if( stack == NULL || newTop == NULL ){
        printf("Erreur : stack or newTop NULL.\n");
        exit(-1);
    }

    newTop->matrix = copyMatrix(matrix, row, col);
    newTop->next = stack->top;
    stack->top = newTop;
}

// Retirement du premier élément de la Pile
// Renvoie une matrice
int** pop(Stack* stack){
    if( stack == NULL ){
        printf("Erreur : stack NULL.\n");
        exit(-1);
    }

    int** tmpMatrice;

    if( stack->top != NULL ){
        tmpMatrice = stack->top->matrix;
        Node* node = stack->top;
        stack->top = stack->top->next;
        free(node); // Libération du noeud qui n'est plus utilisé.
    }
    else{
        printf("Erreur : top NULL.\n");
        exit(-1);
    }

    return tmpMatrice;
}

// Suppression et libération de mémoire pour toutes les matrices contenues dans la pile
// Suppression de libération de mémoire de la pile
void wipeStack(Stack* stack, int row){
    while( stack->top != NULL ){
        // Libération de la deuxième dimension de notre matrice
        for(int i=0; i < row; ++i){
            if( stack->top->matrix[i] != NULL ){
                free(stack->top->matrix[i]);
            }
            else{
                printf("Erreur : wipeStack [%d] NULL.\n", i);
                exit(-1);
            }
        }
        free( stack->top->matrix ); // Libération de la première dimension

        Node* top = stack->top;
        stack->top = stack->top->next;
        free(top);
    }

    free(stack);
}

// Affiche toutes les matrices stockées dans la pile
void printAllStack(Stack* stack, int row, int col){
    Node* index = stack->top;

    printf("-- AFFICHAGE PILE MATRICE --\n");
    while( index != NULL ){
        printMatrix(index->matrix, row, col);
        index = index->next;
    }
    printf("-- FOND DE PILE --\n");
}

/*
GESTION MATRICE
*/

// Affiche une matrice row*col
void printMatrix(int** matrix, int row, int col){
    int i, j;
    printf("{\n");
    for(i = 0; i < row; ++i){
        for(j = 0; j < col; ++j){
            printf("[ %d ]", matrix[i][j]);
        }
        printf("\n");
    }
    printf("}\n");
}

// Remet à 0 une matrice row*col
void resetMatrix(int** matrix, int row, int col){
    for(int i=0; i < row; ++i){
        for(int j=0; j < col; ++j){
            matrix[i][j] = 0;
        }
    }
}

// Créer une nouvelle matrice row*col
int** createNewMatrix(int row, int col){
    int** newMatrix = malloc( row * sizeof(int*));
    if(newMatrix != NULL){
        for(int i = 0; i < row; ++i){
            newMatrix[i] = malloc( col * sizeof(int) );
            if( (newMatrix[i] == NULL) ){
                printf("Erreur : newMatrice[%d] NULL.\n", i);
                exit(-1);
            }
        }
    }
    else{
        printf("Erreur : newMatrice, première dimension NULL.\n");
        exit(-1);
    }

    resetMatrix(newMatrix, row, col);
    return newMatrix;
}

// Copie par valeur d'une matice row*col vers une nouvelle row*col
int** copyMatrix(int** sourceMatrix, int row, int col){
    int** newMatrice;
    newMatrice = createNewMatrix(row, col);
    for(int i=0; i < row; ++i){
        for(int j=0; j < col; ++j){
            newMatrice[i][j] = sourceMatrix[i][j];
        }
    }

    return newMatrice;
}







Coords findLastModif(int **domaines, int nbPigeons){
    Coords coords;
    coords.x = -1;
    coords.y = -1;
    for(int i = 0; i < nbPigeons; ++i){
        for(int j = 0; j < nbPigeons - 1; ++j){
            if(domaines[i][j] == 1){
                coords.x = i;
                coords.y = j;
            }
        }
    }
    return coords;
}

void fillColumns(int **domaines, int i, int j, int nbPigeons, int value){
    for(int k = i; k < nbPigeons; ++k)
        domaines[k][j] = value;
}
