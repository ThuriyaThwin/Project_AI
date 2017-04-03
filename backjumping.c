#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"

/*
    COMPILATION :

    gcc -Wall -o backjumping backjumping.c
*/

void backjumpingPigeons(int nbValue, int nbDomaine, int showMatrix){

    printf("Init BackJumping avec %d valeur & %d domaine.\n", nbValue, nbDomaine);
    int** matrixDomaine = createNewMatrix(nbValue, nbDomaine);                          // Initialisation d'une matrice initiale
    Stack* stack = initStack();                                                         // Initialisation de la pile de matrice
    Stack* result = initStack();                                                        // Initialisation pile des résultats positifs

    int i, j;                                                                           // Itérateurs boucle for
    int resultFound = 0;                                                                // Booleen indiquant si au moins un résultat a été trouvé
    int constraintInRow;                                                                // stock le resultat de checkForConstraintInRow
    int constraintInCol;                                                                // checkForConstraintInCol
    int deepestViolatedConstraint = nbValue;                                            // Sauvegarde de la contrainte violée la plus profonde

    clock_t begin = clock();                                                            // Démarrage du compteur de temps

    for(i=0; i < nbValue; ){

        if( matrixDomaine[0][(nbDomaine-1)] == -1 ) break;                              // Si le domaine du premier pigeon à été entièrement parcouru -> arrêt.
        if( nbDomaine == 0 ){                                                           // Si le nombre de domaine == 0, impossible de réaliser un quelconque parcour
            printf("nbDomaine <= 0\n");
            break;
        }

        for(j=0; j < nbDomaine; ){
            if( showMatrix == 1 ) printMatrix(matrixDomaine, nbValue, nbDomaine);
            //printAllStack(stack, nbValue, nbDomaine);

            constraintInCol = checkForConstraintInCol(matrixDomaine, j, nbValue);       // Test de contrainte entre la valeur i et toutes les autres

            if( constraintInCol < 0 ){                                                  // Cas où aucune contrainte est violée
                matrixDomaine[i][j] = 1;                                                // Incrémentation de la valeur i

                if( i == (nbValue-1) ){                                                 // SOLUTION TROUVEE si i == dernière valeur à incrémenter
                    ++resultFound;                                                      // Booleen
                    push(result, matrixDomaine, nbValue, nbDomaine);                    // Sauvegarde du résultat dans la pile créée à cet effet

                    matrixDomaine = pop_n_time(stack, i, nbValue);                // Retour à la matrice initiale, où la première valeur à réussi à être incrémentée
                    constraintInRow = checkForConstraintInRow(matrixDomaine, 0, nbDomaine);
                    i=0;                                        // On repart de cette valeur qui est en cause de l'échec
                    j=constraintInRow;
                    matrixDomaine[i][j] = -1;                                           // Tout en indiquant que la valeur a été vu
                    deepestViolatedConstraint = nbValue;
                    ++j;
                }
                else{                                                                   // Toutes les valeurs ne sont pas encore incrémentées, on passe donc à la suivante
                    push(stack, matrixDomaine, nbValue, nbDomaine);                     // Sauvegarde de la matrice dans la pile
                    deepestViolatedConstraint = nbValue;
                    j=0;                                                                // Retest de toutes les valeurs possible pour un domaine de i
                    ++i;                                                                // Décalage vers le bas dans notre matrice
                }
            }
            else {                                                                      // Cas où une contrainte est violée ( on s'arrête la première trouvée )

                if( constraintInCol < deepestViolatedConstraint ){
                    deepestViolatedConstraint = constraintInCol;                        // Sauvegarde de la contrainte ( la plus haute ici dans les valeurs )
                }

                matrixDomaine[i][j] = -1;                                               // Impossibilité d'incrémenter, on place -1

                if( j == (nbDomaine-1) ){                                               // Test pour savoir si tous le domaine d'une valeur i a été parcouru
                    if( i == (nbValue-1) ){                                             // Test pour savoir si i est la dernière de toutes les valeurs
                        int nbJump = (nbValue-1) - deepestViolatedConstraint;
                        matrixDomaine = pop_n_time(stack, nbJump, nbValue);             // On dépile jusqu'à trouver la matrice qui correspond à la plus haute contrainte violée

                        constraintInRow = checkForConstraintInRow(matrixDomaine, deepestViolatedConstraint, nbDomaine);
                        i=deepestViolatedConstraint;                                    // On repart de cette valeur qui est en cause de l'échec
                        j=constraintInRow;
                        matrixDomaine[i][j] = -1;                                       // Tout en indiquant que la valeur a été vu
                        deepestViolatedConstraint = nbValue;
                    }
                    else{
                        matrixDomaine = pop(stack);                                     // On dépile la précédente matrice sauvegardée
                        constraintInRow = checkForConstraintInRow(matrixDomaine, i-1, nbDomaine);
                        --i;
                        j=constraintInRow;
                        matrixDomaine[i][j] = -1;
                                                                                    // Retour en arrière de 1
                        deepestViolatedConstraint = nbValue;
                    }
                }

                ++j;                                                                    // Décalage vers la droite, prochaine valeur de domaine pour la valeur i
            }
        }
    }
    clock_t end = clock();

    if( resultFound > 0 ){
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


void backjumpingCheckers(int nbValue, int nbDomaine, int showMatrix){

    printf("Init BackJumping avec %d valeur & %d domaine.\n", nbValue, nbDomaine);
    int** matrixDomaine = createNewMatrix(nbValue, nbDomaine);                          // Initialisation d'une matrice initiale
    Stack* stack = initStack();                                                         // Initialisation de la pile de matrice
    Stack* result = initStack();                                                        // Initialisation pile des résultats positifs

    int i, j;                                                                           // Itérateurs boucle for
    int resultFound = 0;                                                                // Booleen indiquant si au moins un résultat a été trouvé
    int constraintInRow;                                                                // stock le resultat de checkForConstraintInRow
    int constraintInCol;                                                                // checkForConstraintInCol
    int deepestViolatedConstraint = nbValue;                                            // Sauvegarde de la contrainte violée la plus profonde

    clock_t begin = clock();                                                            // Démarrage du compteur de temps

    for(i=0; i < nbValue; ){

        if( matrixDomaine[0][(nbDomaine-1)] == -1 ) break;                              // Si le domaine du premier pigeon à été entièrement parcouru -> arrêt.
        if( nbDomaine == 0 ){                                                           // Si le nombre de domaine == 0, impossible de réaliser un quelconque parcour
            printf("nbDomaine <= 0\n");
            break;
        }

        for(j=0; j < nbDomaine; ){
            if( showMatrix == 1 ) printMatrix(matrixDomaine, nbValue, nbDomaine);
            //printAllStack(stack, nbValue, nbDomaine);

            constraintInCol = checkForConstraintInCol(matrixDomaine, j, nbValue);       // Test de contrainte entre la valeur i et toutes les autres

            // A utiliser pour les reines
            int constraintInDiagonal = checkForConstraintInDiagonal(matrixDomaine, i, j, nbDomaine, nbValue);

            if( constraintInCol < 0 && constraintInDiagonal < 0 ){                                                  // Cas où aucune contrainte est violée
                matrixDomaine[i][j] = 1;                                                // Incrémentation de la valeur i

                if( i == (nbValue-1) ){                                                 // SOLUTION TROUVEE si i == dernière valeur à incrémenter
                    ++resultFound;                                                      // Booleen
                    push(result, matrixDomaine, nbValue, nbDomaine);                    // Sauvegarde du résultat dans la pile créée à cet effet

                    matrixDomaine = pop_n_time(stack, i, nbValue);                // Retour à la matrice initiale, où la première valeur à réussi à être incrémentée
                    constraintInRow = checkForConstraintInRow(matrixDomaine, 0, nbDomaine);
                    i=0;                                        // On repart de cette valeur qui est en cause de l'échec
                    j=constraintInRow;
                    matrixDomaine[i][j] = -1;                                           // Tout en indiquant que la valeur a été vu
                    deepestViolatedConstraint = nbValue;
                    ++j;
                }
                else{                                                                   // Toutes les valeurs ne sont pas encore incrémentées, on passe donc à la suivante
                    push(stack, matrixDomaine, nbValue, nbDomaine);                     // Sauvegarde de la matrice dans la pile
                    deepestViolatedConstraint = nbValue;
                    j=0;                                                                // Retest de toutes les valeurs possible pour un domaine de i
                    ++i;                                                                // Décalage vers le bas dans notre matrice
                }
            }
            else {                                                                      // Cas où une contrainte est violée ( on s'arrête la première trouvée )

                if( constraintInCol < 0 && constraintInDiagonal != -1 )
                    constraintInCol = constraintInDiagonal;

                if( constraintInCol != - 1 && constraintInDiagonal != - 1){
                    if( constraintInCol > constraintInDiagonal )
                        constraintInCol = constraintInDiagonal;
                }

                if( constraintInCol < deepestViolatedConstraint ){
                    deepestViolatedConstraint = constraintInCol;                        // Sauvegarde de la contrainte ( la plus haute ici dans les valeurs )
                }

                matrixDomaine[i][j] = -1;                                               // Impossibilité d'incrémenter, on place -1

                if( j == (nbDomaine-1) ){                                               // Test pour savoir si tous le domaine d'une valeur i a été parcouru
                    if( i == (nbValue-1) ){                                             // Test pour savoir si i est la dernière de toutes les valeurs
                        int nbJump = (nbValue-1) - deepestViolatedConstraint;
                        matrixDomaine = pop_n_time(stack, nbJump, nbValue);             // On dépile jusqu'à trouver la matrice qui correspond à la plus haute contrainte violée

                        constraintInRow = checkForConstraintInRow(matrixDomaine, deepestViolatedConstraint, nbDomaine);
                        i=deepestViolatedConstraint;                                    // On repart de cette valeur qui est en cause de l'échec
                        j=constraintInRow;
                        matrixDomaine[i][j] = -1;                                       // Tout en indiquant que la valeur a été vu
                        deepestViolatedConstraint = nbValue;
                    }
                    else{
                        matrixDomaine = pop(stack);                                     // On dépile la précédente matrice sauvegardée
                        constraintInRow = checkForConstraintInRow(matrixDomaine, i-1, nbDomaine);
                        --i;
                        j=constraintInRow;
                        matrixDomaine[i][j] = -1;
                                                                                    // Retour en arrière de 1
                        deepestViolatedConstraint = nbValue;
                    }
                }

                ++j;                                                                    // Décalage vers la droite, prochaine valeur de domaine pour la valeur i
            }
        }
    }
    clock_t end = clock();

    if( resultFound > 0 ){
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
