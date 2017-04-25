#include <stdio.h>
#include <stdlib.h>

#include "backj.h"
#include "matrix.h"

/*
    Procédure de backJumping sans heuristique :
*/
void backjumping(CSP* csp){
    /*
        Matrice permettant de stocker la contrainte violée la plus profonde pour chaque variable i
    */
    int** matrixViolatedConstraint = createNewMatrix(csp->nbVariable, csp->nbValue);

    //int checkC; // Variable temporaire prennant le résultat de la fonction checkForConstraint
    int Iposition = 0; // index i de notre matrice de Domaines
    int Jposition = 0;  // index j de notre matrice de Domaines

    long long unsigned int nb = 0;

    // TANT QUE la toute dernière valeur de la première variable n'est pas "vue", on continue
    while(csp->matrixDomain[0][csp->nbValue-1] != -1){

        ++nb;
        csp->matrixDomain[Iposition][Jposition] = 1;
        matrixViolatedConstraint[Iposition][Jposition] = checkForConstraint(csp, Iposition);

        if( matrixViolatedConstraint[Iposition][Jposition] < 0 ){
            addCheckedValue(csp, Iposition, Jposition);

            if( Iposition < csp->nbVariable-1 ){
                ++Iposition;
                Jposition=0;
                initTab(csp->matrixDomain[Iposition], csp->nbValue, 0);
            }
            else{
                csp->matrixDomain[Iposition][Jposition] = -1;

                //Dès qu'une solution est trouvée, on revient en arrière //backtrack
                --Iposition;
                while(Iposition > 0 && csp->tabCheckedValue[Iposition] == csp->nbValue-1){
                    --Iposition;
                }

                Jposition = csp->tabCheckedValue[Iposition];
                csp->matrixDomain[Iposition][Jposition] = -1;

                ++Jposition;
            }
        }
        else{
            if( Jposition == csp->nbValue-1 ){

                if( Iposition == csp->nbVariable-1 ){
                    //TROUVER LA VARIABLE LA PLUS PROFONDE EN CAUSE DANS L ECHEC
                    int max = 0;
                    for(int k=0; k < csp->nbValue; ++k){
                        if( matrixViolatedConstraint[Iposition][k] > max )
                            max = matrixViolatedConstraint[Iposition][k];
                    }
                    Iposition = max;
                }
                else{
                    --Iposition;
                }

                while(Iposition > 0 && csp->tabCheckedValue[Iposition] == csp->nbValue-1){
                    --Iposition;
                }

                Jposition = csp->tabCheckedValue[Iposition];
                csp->matrixDomain[Iposition][Jposition] = -1;
            }

            ++Jposition;
        }

    }

    printf("\n>>>> %llu itérations.\n", nb);
    freeMatrix(matrixViolatedConstraint, csp->nbValue);
}
