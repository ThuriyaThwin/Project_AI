#include <stdio.h>
#include <stdlib.h>

#include "backj.h"
#include "matrix.h"

/*
    Procédure de backJumping sans heuristique :
*/
void backjumping(CSP* csp){

    int* tabDeepestVariable = createNewTab(csp->nbVariable);
    for(int i=0; i < csp->nbVariable; ++i){
        tabDeepestVariable[i] = csp->nbVariable-1;
    }

    //int deepestVariable = csp->nbVariable-1; // variable la plus haute qui est en cause de l'échec
    int checkC; // Variable temporaire prennant le résultat de la fonction checkForConstraint
    int Iposition = 0; // index i de notre matrice de Domaines
    int Jposition = 0;  // index j de notre matrice de Domaines

    while(csp->matrixDomain[0][csp->nbValue-1] != -1){

        //sleep(1);
        csp->matrixDomain[Iposition][Jposition] = 1;
        //printMatrix(csp->matrixDomain, csp->nbVariable, csp->nbValue);
        checkC = checkForConstraint(csp, Iposition);
        //printMatrix(csp->matrixDomain, csp->nbVariable, csp->nbValue);
        //printf("\n");

        printf("[%d][%d]\n\n", Iposition, Jposition);


        if( checkC < 0 ){ // Contrainte non-violée
            addCheckedValue(csp, Iposition, Jposition);
            //tabDeepestVariable[Iposition] = csp->nbVariable-1;

            // Cas où toutes les variables ne sont pas encore testées
            if( Iposition < csp->nbVariable-1 ){
                ++Iposition;
                Jposition = 0;
            }

            // Cas où toutes les variables ont trouvé au moins une valeurs
            else{
                printAllStack(csp->results, csp->nbVariable);

                // Cas où la toute dernière variable n'a pas encore testé toutes les valeurs
                if( Jposition < csp->nbValue-1 ){
                    csp->matrixDomain[Iposition][Jposition] = -1;
                    ++Jposition;
                }
                // Cas où toutes les valeurs ont été associé à la dernière variable
                else{
                    tabDeepestVariable[Iposition] = csp->nbVariable-1;
                    --Iposition;
                    csp->matrixDomain[Iposition][ csp->tabCheckedValue[Iposition] ] = -1;
                    Jposition = csp->tabCheckedValue[Iposition] + 1;
                }
            }
        }

        else{ // Contrainte violée
            if(checkC < tabDeepestVariable[Iposition] ) tabDeepestVariable[Iposition] = checkC;

            if( Jposition == csp->nbValue-1 ){

                //printMatrix(csp->matrixDomain, csp->nbVariable, csp->nbValue);
                //printTab(csp->tabCheckedValue, csp->nbVariable);

                resetMatrix(csp->matrixDomain, csp->nbVariable, csp->nbValue);
                for(int i=0; i < tabDeepestVariable[Iposition]; ++i)
                    csp->matrixDomain[i][ csp->tabCheckedValue[i] ] = 1;

                Iposition = tabDeepestVariable[Iposition];
                Jposition = csp->tabCheckedValue[Iposition];
                csp->matrixDomain[Iposition][Jposition] = -1;
                tabDeepestVariable[Iposition] = csp->nbVariable-1;
            }

            ++Jposition;
        }


    }

    free( tabDeepestVariable );
}
