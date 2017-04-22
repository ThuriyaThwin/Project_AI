#include <stdio.h>
#include <stdlib.h>

#include "backj.h"
#include "matrix.h"

/*
    Procédure de backJumping sans heuristique :
*/
void backjumping(CSP* csp){

    int checkC; // Variable temporaire prennant le résultat de la fonction checkForConstraint
    int Iposition = 0; // index i de notre matrice de Domaines
    int Jposition = 0;  // index j de notre matrice de Domaines

    while(csp->matrixDomain[0][csp->nbValue-1] != -1){

        //sleep(1);

        csp->matrixDomain[Iposition][Jposition] = 1;
        checkC = checkForConstraint(csp, Iposition);

        if( checkC < 0 ){ // Contrainte non-violée
            //printf("{ [%d][%d] }\n", Iposition, Jposition);
            addCheckedValue(csp, Iposition, Jposition);

            // Cas où toutes les variables ne sont pas encore testées
            if( Iposition < csp->nbVariable-1 ){
                ++Iposition;
                Jposition = 0;
            }

            // Cas où toutes les variables ont trouvé au moins une valeurs
            else{
                csp->matrixDomain[Iposition][Jposition] = -1;
                /*
                    Solution trouvée, mais tester si possible d'aller encore sur la droite, sinon backtrack
                */
                if( Jposition == csp->nbValue-1 ){
                    --Iposition;
                    // On fait attention à backtrack sur une variable où toutes les valeurs n'ont pas déjà été testées
                    while( Iposition > 0 && csp->tabCheckedValue[Iposition] == csp->nbValue-1 ){
                        Jposition = csp->tabCheckedValue[Iposition];
                        csp->matrixDomain[Iposition][Jposition] = -1;
                        --Iposition;
                    }

                    Jposition = csp->tabCheckedValue[Iposition];
                    csp->matrixDomain[Iposition][Jposition] = - 1;
                }

                ++Jposition;
            }
        }

        else{ // Contrainte violée

            // Cas où toutes les valeurs pour une variable ont été testé
            if( Jposition == csp->nbValue-1 ){

                csp->matrixDomain[Iposition][Jposition] = -1;

                //if( Iposition == csp->nbVariable-1 ){ Iposition = checkC; }
                //else { --Iposition; }
                --Iposition;
                // On fait attention à backtrack sur une variable où toutes les valeurs n'ont pas déjà été testées
                while( Iposition > 0 && csp->tabCheckedValue[Iposition] == csp->nbValue-1 ){
                    Jposition = csp->tabCheckedValue[Iposition];
                    csp->matrixDomain[Iposition][Jposition] = -1;
                    --Iposition;
                }

                Jposition = csp->tabCheckedValue[Iposition];
                csp->matrixDomain[Iposition][Jposition] = - 1;
            }

            ++Jposition;
        }
    }
}
