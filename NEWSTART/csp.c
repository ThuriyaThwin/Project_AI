#include <stdio.h>
#include <stdlib.h>

#include "csp.h"
#include "matrix.h"
#include "stack.h"

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
    newCSP->matrixDomain = createNewMatrix(nbVariable, nbValue);

    // Allocation Tableau de sauvegarde d'état
    newCSP->tabCheckedValue = createNewTab(nbVariable);
    //resetCheckedValue(newCSP, 0, nbVariable-1); // On met à -1 tous les états sauvegardés

    // Allocation de la pile de résultats
    newCSP->results = initStack();
    newCSP->nbResult = 0;

    newCSP->nbVariable = nbVariable;
    newCSP->nbValue = nbValue;

    return newCSP;
}

/*
    Libération de mémoire pour le CSP
*/
void freeCSP(CSP* csp){

    // Libération de la mémoire allouée pour les différents tableaux :
    free(csp->tabCheckedValue);
    freeMatrix(csp->matrixDomain, csp->nbVariable);
    freeConstraintMatrix(csp->matrixConstraint, csp->nbVariable, csp->nbValue);

    // Libération mémoire pile
    wipeStack(csp->results, csp->nbResult);

    // Libération de mémoire pour la structure CSP
    free( csp );
}

/*
    AFFICHAGE CSP :
*/
void printCSP(CSP* csp){
    printf("\n\n----| CSP |----\n");
    printf("\n+++ CONTRAINTES & TUPLES +++\n");

    for(int i=0; i < csp->nbVariable; ++i){
        for(int j=0; j < csp->nbVariable; ++j){
            if( csp->matrixConstraint[i][j] != NULL ){
                printf(">>> CONTRAINTE (%d,%d) <<<\n", i, j);
                printMatrix(csp->matrixConstraint[i][j], csp->nbValue, csp->nbValue);
            }
        }
    }

    printf("\n+++ DOMAINE +++\n");
    printMatrix(csp->matrixDomain, csp->nbVariable, csp->nbValue);

    printf("\n+++ RESULTAT +++\n");
    printAllStack(csp->results, csp->nbResult);

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

void freeConstraintMatrix(int**** matrix, int nbConstraintElement, int nbTupleElement){

    // Suppression une seule fois de la matrice de tuple
    freeMatrix(matrix[0][1], nbTupleElement);

    for(int i=0; i < nbConstraintElement; ++i){
        /*

            Impossible à réaliser car dans le cas du pigeon, toutes les contraintes pointes vers le même tuple

        */
        //for(int j=0; j < nbConstraintElement; ++j)
            //if( matrix[i][j] != NULL )
                //freeMatrix(matrix[i][j], nbTupleElement);

        free( matrix[i] );
    }
    free( matrix );
}

/*
    Fonction à utiliser pour savoir si la valeur associée à une variable ne viole aucune contrainte avec les autres variables.

    En entrée :
        l'index de la variable (ligne de notre tableau de domaine) que l'on vient de modifier (colonne de notre tableau de domaine mise à 1).

    Si il existe une contrainte entre la variable indexVariable & i
        -> recherche une correspondance dans les tuples permis (couple de valeur permis)

    renvoi 1 si contrainte trouvée
    renvoi 0 si aucune contrainte trouvée
*/
int checkForConstraint(CSP* csp, int indexVariable){
    for(int i=0 ; i < indexVariable ; ++i )
        if( csp->matrixConstraint[indexVariable][i] != NULL )
            if( checkAllowedCouple(csp, indexVariable, i) > 0 )
                return 1;

    return 0;
}

/*
    Récupère la valeur prise par deux variables dans leurs domaines respectifs.
    Renvoi 1 si la contrainte est violée.
    Renvoi 0 si la contrainte est non-violée.
*/
int checkAllowedCouple(CSP* csp, int indexVarOne, int indexVarTwo){
    // Recherche de la valeur prise par nos deux variables :
    int colOne = -1;
    int colTwo = -1;

    for(int i=0; i < csp->nbValue; ++i){
        if( csp->matrixDomain[indexVarOne][i] == 1 ) colOne = i;    // valeur variable1
        if( csp->matrixDomain[indexVarTwo][i] == 1 ) colTwo = i;    // valeur variable2
        if( (colOne >= 0) && (colTwo >= 0) ) break;
    }

    // On regarde si le Tuple ( colOne, colTwo ) == 1 :
    // Couple autorisé par la contrainte -> contrainte non-violée
    if( csp->matrixConstraint[indexVarOne][indexVarTwo][colOne][colTwo] == 1 )
        return 0;

    // Sinon, si == 0 :
    // couple non-autorisé par la contrainte -> contrainte violée

    // MAJ du domaine de la variable, on indique par quelle autre variable elle a été filtrée
    // On indique -1 * index de la variable
    // Cela premettra notamment lors du BackJumping par exemple, de connaître plus tard la plus haute valeur "en faute" dans l'arbre de recherche
    csp->matrixDomain[indexVarOne][colOne] = -indexVarTwo;
    return 1;
}

/*

    Lorsqu'un état réussi -> aucunes contraintes violées par la variable i, lorsqu'elle prend la valeur j ;
                            --> matriceDomaine[i][j] == 1.

    On sauvegarde la valeur prise par i dans un tableau.
    Cela nous permettra plus tard de revenir dessus, et de reconstruire notre matrice grâce aux valeurs inscrites dans ce tableau (exemple: backjumping).

*/
void addCheckedValue(CSP* csp, int I_position, int J_position){
    csp->tabCheckedValue[I_position] = J_position;

    // Solution TROUVEE
    if( I_position == csp->nbVariable-1 ){
        push(csp->results, csp->tabCheckedValue, csp->nbVariable);
        ++csp->nbResult;
    }

}

/*

void resetCheckedValue(CSP* csp, int fromA, int toB){
    for(int i=fromA; i <= toB; ++i)
        csp->tabCheckedValue[i] = -1;
}

*/
