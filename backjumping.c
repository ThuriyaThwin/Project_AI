#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.c"

/*
    COMPILATION :

    gcc -Wall -o backjumping backjumping.c
*/

void backjumping(int nbValue, int nbDomaine, int showMatrix){
    int i, j;

    printf("Init BackJumping avec %d valeur & %d domaine.\n", nbValue, nbDomaine);
    int** matrixDomaine = createNewMatrix(nbValue, nbDomaine); // Initialisation d'une matrice
    Stack* stack = initStack(); // Initialisation de la pile de matrice

    int resultFound = 0;    // Booleen indiquant si au moins un résultat a été trouvé
    Stack* result = initStack(); // Initialisation pile des résultats positifs

    int constraintInRow; // checkForConstraintInRow
    int constraintInCol; // checkForConstraintInCol

    // Sauvegarde de la contrainte violée la plus profonde
    int deepestViolatedConstraint = nbValue;

    clock_t begin = clock();

    for(i=0; i < nbValue; ){
        // Si le domaine du premier pigeon à été entièrement parcouru -> arrêt.
        if( matrixDomaine[0][(nbDomaine-1)] == -1 ) break;
        if( nbValue == 1 ) break;

        for(j=0; j < nbDomaine; ){
            // On test si un pigeon est déjà placé dans le nid j
            constraintInCol = checkForConstraintInCol(matrixDomaine, j, nbValue);

            // Dans le cas où aucun pigeon n'est déjà présent dans la colonne :
            if( constraintInCol < 0 ){
                matrixDomaine[i][j] = 1; // Le pigeon i est donc placé dans le nid j

                /*
                    Nous regardons dans une premier temps si il est possible de de passer au pigeon i+1
                    Dans le cas où sela ne serait pas possible  -> nous sommes arrivés au dernier pigeon
                                                                -> nous avons réussi à placer tous nos pigeons
                                                                -> solution alors trouvée
                    Cas normalement impossible à trouver.
                */
                // SOLUTION TROUVEE si i == dernier pigeon
                if( i == (nbValue-1) ){
                    //printf("\nSOLUTION TROUVEE :\n");

                    resultFound = 1;
                    push(result, matrixDomaine, nbValue, nbDomaine);

                    matrixDomaine = pop_n_time(stack, i, nbValue); // On revient à l'état de la matrice où pigeon 1 à réussi à être placé
                    matrixDomaine[0][j] = -1;   // ça valeur est mise à -1 pour indiqué qu'on a bien vu cette ligne
                    i=0;
                    ++j; // Décalage vers la droite
                    deepestViolatedConstraint = nbValue;
                }
                else{
                    push(stack, matrixDomaine, nbValue, nbDomaine); // Sauvegarde de la matrice dans la pile
                    deepestViolatedConstraint = nbValue;
                    j=0;
                    ++i;
                }
            }
            else { // Dans le cas où un pigeon est déjà placé dans la colonne :
                // Sauvegarde de la contrainte
                if( constraintInCol < deepestViolatedConstraint ){
                    deepestViolatedConstraint = constraintInCol;
                }
                matrixDomaine[i][j] = -1; // Nous indiquons dans la matrice qu'il n'est pas possible de placer de pigeon à cet endroit

                /* Test pour savoir si tous les nids j pour le pigeon i ont été testés */
                if( j == (nbDomaine-1) ){
                    /*
                        Dans le cas où le pigeon i a testé tous les nids j sans pouvoir trouver de place :
                            - on test dans un premier temps si nous avons aussi parcourus l'ensemble des pigeons i
                                -> si c'est le cas, alors on est dans un cas de backjumping, on revient sur la
                                contrainte violée la plus haute dans l'arbre. ( pop de la pile )
                                -> sinon, il s'agit d'un simple backtrack, on revient sur la valeur du pigeon i-1
                    */
                    if( i == (nbValue-1) ){
                        // TOUS LES PIGEONS ONT ETE TRAITES
                        // On revient à l'état de la matrice où la contrainte la plus haute à été violée
                        // on dépile la pile nbJump fois pour atteindre la contrainte +haute violée
                        int nbJump = (nbValue-1) - deepestViolatedConstraint;
                        matrixDomaine = pop_n_time(stack, nbJump, nbValue);

                        // On récupère l'emplacement du 1 dans le domaine du pigeon qui est en cause de l'echec
                        constraintInRow = checkForConstraintInRow(matrixDomaine, deepestViolatedConstraint, nbDomaine);
                        i=deepestViolatedConstraint;
                        j=constraintInRow;
                        matrixDomaine[i][j] = -1;
                        deepestViolatedConstraint = nbValue;
                    }
                    else{
                        matrixDomaine = pop(stack); // On dépile la précédente matrice sauvegardée
                        constraintInRow = checkForConstraintInRow(matrixDomaine, i-1, nbDomaine);
                        matrixDomaine[i-1][constraintInRow] = -1;
                        --i; // On revient en arrière de 1
                        deepestViolatedConstraint = nbValue;
                    }
                }

                ++j;
            }
            if( showMatrix == 1 ) printMatrix(matrixDomaine, nbValue, nbDomaine);
        }
    }
    clock_t end = clock();

    if( resultFound == 1 ){
        printf("SOLUTION(S) TROUVEE(S):\n");
        printAllStack(result, nbValue, nbDomaine);
    }
    else
        printf("0 SOLUTIONS POUR %d PIGEONS\n", nbValue);

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("TEMPS EXECUTION CPU : %lf secondes.\n", time_spent);

    // Libération de mémoire
    wipeStack(stack, nbValue);
    wipeStack(result, nbValue);
    wipeMatrix(matrixDomaine, nbValue);
}
