#include <stdio.h>
#include <stdlib.h>
#include "util.c"

int main(int argc, char** argv){
    if( argc != 2 ){
        printf("erreur arguments\n");
        exit(-1);
    }

    int i, j;
    int nbPigeons = atoi(argv[1]); // Nombre de pigeon indiqués parl l'utilisateur.
    int nbNids = (nbPigeons-1);     // Nombre de nids, ici automatiquement pigeon - 1.

    printf("Démarrage avec %d pigeons & %d nids.\n", nbPigeons, nbNids);
    int** matrixDomaine = createNewMatrix(nbPigeons, nbNids); // Initialisation d'une matrice
    Stack* stack = initStack(); // Initialisation de la pile de matrice

    int constraintInRow; // checkForConstraintInRow
    int constraintInCol; // checkForConstraintInCol

    // Sauvegarde de la contrainte violée la plus profonde
    int deepestViolatedConstraint = nbPigeons;

    for(i=0; i < nbPigeons; ){
        // Si le domaine du premier pigeon à été entièrement parcouru -> arrêt.
        if( matrixDomaine[0][(nbNids-1)] == -1 ) break;

        for(j=0; j < nbNids; ){
            // On test si un pigeon est déjà placé dans le nid j
            constraintInCol = checkForConstraintInCol(matrixDomaine, j, nbPigeons);

            // Dans le cas où aucun pigeon n'est déjà présent dans la colonne :
            if( constraintInCol < 0 ){
                matrixDomaine[i][j] = 1; // Le pigeon i est donc placé dans le nid j

                //printMatrix(matrixDomaine, nbPigeons, nbNids);

                /*
                    Nous regardons dans une premier temps si il est possible de de passer au pigeon i+1
                    Dans le cas où sela ne serait pas possible  -> nous sommes arrivés au dernier pigeon
                                                                -> nous avons réussi à placer tous nos pigeons
                                                                -> solution alors trouvée
                    Cas normalement impossible à trouver.
                */
                // SOLUTION TROUVEE si i == dernier pigeon
                if( i == (nbPigeons-1) ){
                    printf("\nSOLUTION TROUVEE :\n");

                    matrixDomaine = pop_n_time(stack, i, nbPigeons); // On revient à l'état de la matrice où pigeon 1 à réussi à être placé
                    matrixDomaine[0][j] = -1;   // ça valeur est mise à -1 pour indiqué qu'on a bien vu cette ligne
                    i=0;
                    ++j; // Décalage vers la droite
                    deepestViolatedConstraint = nbPigeons;
                }
                else{
                    push(stack, matrixDomaine, nbPigeons, nbNids); // Sauvegarde de la matrice dans la pile
                    deepestViolatedConstraint = nbPigeons;
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
                //printMatrix(matrixDomaine, nbPigeons, nbNids);

                /* Test pour savoir si tous les nids j pour le pigeon i ont été testés */
                if( j == (nbNids-1) ){
                    /*
                        Dans le cas où le pigeon i a testé tous les nids j sans pouvoir trouver de place :
                            - on test dans un premier temps si nous avons aussi parcourus l'ensemble des pigeons i
                                -> si c'est le cas, alors on est dans un cas de backjumping, on revient sur la
                                contrainte violée la plus haute dans l'arbre. ( pop de la pile )
                                -> sinon, il s'agit d'un simple backtrack, on revient sur la valeur du pigeon i-1
                    */
                    if( i == (nbPigeons-1) ){
                        // TOUS LES PIGEONS ONT ETE TRAITES
                        // On revient à l'état de la matrice où la contrainte la plus haute à été violée
                        // on dépile la pile nbJump fois pour atteindre la contrainte +haute violée
                        int nbJump = (nbPigeons-1) - deepestViolatedConstraint;
                        matrixDomaine = pop_n_time(stack, nbJump, nbPigeons);

                        // On récupère l'emplacement du 1 dans le domaine du pigeon qui est en cause de l'echec
                        constraintInRow = checkForConstraintInRow(matrixDomaine, deepestViolatedConstraint, nbNids);
                        i=deepestViolatedConstraint;
                        j=constraintInRow;
                        matrixDomaine[i][j] = -1;
                        //printMatrix(matrixDomaine, nbPigeons, nbNids);
                        deepestViolatedConstraint = nbPigeons;
                    }
                    else{
                        matrixDomaine = pop(stack);
                        constraintInRow = checkForConstraintInRow(matrixDomaine, i-1, nbNids);
                        matrixDomaine[i-1][constraintInRow] = -1;
                        --i; // On revient en arrière de 1
                        deepestViolatedConstraint = nbPigeons;
                    }
                }

                ++j;
            }
        }
    }

    //printAllStack(stack, nbPigeons, nbNids);
    // Libération de mémoire ----

    wipeStack(stack, nbPigeons);
    wipeMatrix(matrixDomaine, nbPigeons);

    return 0;
}
