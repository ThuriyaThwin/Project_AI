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
    newCSP->nbVariable = nbVariable;
    newCSP->nbValue = nbValue;

    // Allocation Contraintes
    newCSP->matrixConstraint = newConstraintMatrix(newCSP);

    // Allocation Domaines
    newCSP->matrixDomain = createNewMatrix(newCSP->nbVariable, newCSP->nbValue);

    // Allocation Tableau de sauvegarde d'état
    newCSP->tabCheckedValue = createNewTab(newCSP->nbVariable);
    for(int i=0; i < newCSP->nbVariable; ++i)
        newCSP->tabCheckedValue[i] = -1;

    // Allocation de la pile de résultats
    newCSP->results = initStack();
    newCSP->nbResult = 0;

    return newCSP;
}

/*
    Libération de mémoire pour le CSP
*/
void freeCSP(CSP* csp, int flag){

    // Libération de la mémoire allouée pour les différents tableaux :
    free(csp->tabCheckedValue);
    freeMatrix(csp->matrixDomain, csp->nbVariable);

    if(flag == 1) freeConstraintMatrixPigeon(csp);
    if(flag == 2) freeConstraintMatrixDame(csp);

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
        for(int j=i+1; j < csp->nbVariable; ++j){
            if( csp->matrixConstraint[i][j] != NULL ){
                printf(">>> CONTRAINTE (%d,%d) & (%d,%d) <<<\n", i, j, j, i);
                printMatrix(csp->matrixConstraint[i][j], csp->nbValue, csp->nbValue);
            }
        }
    }

    printf("\n----| FIN |----\n");
}


/*    MATRICE       */
/*
 Création de la matrice de contrainte, toutes les contraintes sont initialisés à NULL.
 Ce sera aux différents générateurs de remplir les tuples de ces fameuses contraintes.
*/
int**** newConstraintMatrix(CSP* csp){
    int**** matrixConstraint = malloc( csp->nbVariable * sizeof(int***) );
    for(int i=0; i < csp->nbVariable; ++i){
        matrixConstraint[i] = malloc( csp->nbVariable * sizeof(int**) );
        for(int j=0; j < csp->nbVariable; ++j)
            matrixConstraint[i][j] = NULL;
    }

    return matrixConstraint;
}

void freeConstraintMatrixDame(CSP* csp){

    // Chaque contrainte, pointe toujours vers la même matrice de couple/tuple (en mémoire)
    // On la libère donc une seule fois !

    // Faut-il encore la trouvée :
    for(int i=0; i < csp->nbVariable; ++i){
        for(int j=i+1; j < csp->nbVariable; ++j){
            if( csp->matrixConstraint[i][j] != NULL ){                          // Si il existe bien une matrice de tuple/couple
                freeMatrix( csp->matrixConstraint[i][j], csp->nbValue );        // Libération de mémoire
            }
        }
        free( csp->matrixConstraint[i] );                                           // Libération mémoire matrice contrainte
    }
    free( csp->matrixConstraint );
}

void freeConstraintMatrixPigeon(CSP* csp){

    // Chaque contrainte, pointe toujours vers la même matrice de couple/tuple (en mémoire)
    // On la libère donc une seule fois !

    // Faut-il encore la trouvée :

    int done = 0; // flag
    for(int i=0; i < csp->nbVariable; ++i){

        if( done == 0 ){                                                            // Si la matrice de tuple/couple n'est toujours pas trouvée
            for(int j=0; j < csp->nbVariable; ++j){
                if( csp->matrixConstraint[i][j] != NULL ){                          // Si il existe bien une matrice de tuple/couple
                    freeMatrix( csp->matrixConstraint[i][j], csp->nbValue );        // Libération de mémoire
                    done = 1;                                                       // A éxecuter une seule fois ! // Sinon doublefree corruption
                    break;                                                          // On sort du for
                }
            }
        }

        free( csp->matrixConstraint[i] );                                           // Libération mémoire matrice contrainte
    }
    free( csp->matrixConstraint );
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

    int varWitchConstraint;

    for(int i=0 ; i < indexVariable ; ++i )
        if( csp->matrixConstraint[indexVariable][i] != NULL )
            if( (varWitchConstraint = checkAllowedCouple(csp, indexVariable, i)) >= 0 )
                return varWitchConstraint;

    return -1;
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
        colOne = findValueDomain(csp, indexVarOne, 1);
        colTwo = findValueDomain(csp, indexVarTwo, 1);
        if( (colOne >= 0) && (colTwo >= 0) ) break;
    }

    // On regarde si le Tuple ( colOne, colTwo ) == 1 :
    // Couple autorisé par la contrainte -> contrainte non-violée
    if( csp->matrixConstraint[indexVarOne][indexVarTwo][colOne][colTwo] == 1 )
        return -1;


    csp->matrixDomain[indexVarOne][colOne] = -1;
    return indexVarTwo;
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

int findValueDomain(CSP* csp, int I_position, int theValue){
    for(int i=0; i < csp->nbValue; ++i){
        if( csp->matrixDomain[I_position][i] == theValue ){
            return i;
        }
    }
    return -1;
}
