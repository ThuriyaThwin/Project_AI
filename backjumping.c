#include <stdio.h>
#include <stdlib.h>
#include "util.c"

int findConstraint_Col(int** matrix, int nbRow, int col){
    for(int i=0; i < nbRow; ++i){
        if( matrix[i][col] == 1 )
            return i;
    }
    return -1;
}

int findConstraint_Row(int** matrix, int nbElement, int row){
    for(int i=0; i < nbElement; ++i){
        if( matrix[row][i] == 1 )
            return i;
    }
    return -1;
}

int main(int argc, char** argv){
    if( argc != 2 ){
        printf("erreur arguments\n");
        exit(-1);
    }


    /*

        POUR LE MOMENT ESSAIE COMPLET A LA MAIN

        RIEN D'ITERATIF ENCORE POUR LE MOMENT

        FONCTIONNEMENT DE LA PILE -> OK
        FONCTIONNEMENT MATRICE -> OK

    */



    int i;
    int** domaineInit;
    int nbPigeons = atoi(argv[1]);
    int nbNids = (nbPigeons-1);

    int size = nbPigeons;

    printf("Démarrage avec %d pigeons & %d nids.\n", nbPigeons, nbNids);

    // Initialisation d'une matrice
    domaineInit = createNewMatrix(nbPigeons, nbNids);

    // Initialisation de la pile de matrice
    Stack* stack = initStack();

    // Initialisation du premier cas : pigeon 1 -> nid 1
    domaineInit[0][0] = 1;

    // Affichage vérification
    printMatrix(domaineInit, nbPigeons, nbNids);

    // Ajout dans la pile de l'état de la matrice à ce moment là, avant toutes nouvelles modifications
    push(stack, domaineInit, nbPigeons, nbNids);
    --size;

    printf("\n{ %d }\n\n", size);

    // Passage au pigeon 2, nous rechercons dans un premier temps si nous pouvons l'insérer dans le nid 1
    int cRow = findConstraint_Col(domaineInit, nbPigeons, 0);
    int cCol;

    // Dans le cas où un pigeon est déjà présent dans la colonne 0 :
    if( cRow >= 0 ){
        cCol = findConstraint_Row(domaineInit, nbNids, 0);

        if( nbNids-cCol > 0 ){
            domaineInit[1][0] = -1;
        }
    }
    printMatrix(domaineInit, nbPigeons, nbNids);

    // Domaine 1, colonne 1
    cRow = findConstraint_Col(domaineInit, nbPigeons, 1);
    // Dans le cas où un pigeon est déjà présent dans la colonne 0 :
    if( cRow >= 0 ){
        cCol = findConstraint_Row(domaineInit, nbNids, 0);

        if( nbNids-cCol > 0 ){
            domaineInit[1][0] = -1;
        }
    }
    else{
        domaineInit[1][1] = 1;
        push(stack, domaineInit, nbPigeons, nbNids);
        --size;

        printf("\n{ %d }\n\n", size);
    }
    printMatrix(domaineInit, nbPigeons, nbNids);




    printAllStack(stack, nbPigeons, nbNids);
    //printMatrix(stack->top->matrix, nbPigeons, nbNids);


    // Libération de mémoire ----

    wipeStack(stack, nbPigeons);

    for(i=0; i < nbPigeons; ++i){
        free(domaineInit[i]);
    }

    free( domaineInit );

    return 0;
}
