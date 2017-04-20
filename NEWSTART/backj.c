#include <stdio.h>
#include <stdlib.h>

#include "backj.h"
#include "matrix.h"

/*
    Procédure de backJumping sans heuristique :
*/
void backjumping(CSP* csp){

    int deepestVariable = csp->nbVariable-1; // variable la plus haute qui est en cause de l'échec
    int checkC; // Variable temporaire prennant le résultat de la fonction checkForConstraint
    int Iposition = 0; // index i de notre matrice de Domaines
    int Jposition = 0;  // index j de notre matrice de Domaines

    while(csp->matrixDomain[0][csp->nbValue-1] != -1){
        csp->matrixDomain[Iposition][Jposition] = 1;
        checkC = checkForConstraint(csp, Iposition);

        if( checkC < 0 ){ // Contrainte non-violée
            addCheckedValue(csp, Iposition, Jposition);

            deepestVariable = csp->nbVariable-1;

            // test pour savoir si toucher fond

            /*if( Iposition > csp->nbVariable-1 ){
                printf("OHLOL\n");
                exit(0);
            }*/

            ++Iposition;
            Jposition = 0;
        }

        else{ // Contrainte violée
            if(checkC < deepestVariable) deepestVariable = checkC;

            if( Jposition == csp->nbValue-1 ){
                /*
                printMatrix(csp->matrixDomain, csp->nbVariable, csp->nbValue);
                printTab(csp->tabCheckedValue, csp->nbVariable);
                */

                resetMatrix(csp->matrixDomain, csp->nbVariable, csp->nbValue);
                for(int i=0; i < deepestVariable; ++i)
                    csp->matrixDomain[i][ csp->tabCheckedValue[i] ] = 1;


                Iposition = deepestVariable;
                Jposition = csp->tabCheckedValue[Iposition];
                csp->matrixDomain[Iposition][Jposition] = -1;
                deepestVariable = csp->nbVariable-1;
            }

            ++Jposition;
        }


    }
}
