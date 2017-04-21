#include <stdio.h>
#include <stdlib.h>

#include "backj.h"
#include "matrix.h"

/*
    Procédure de backJumping sans heuristique :
*/
void backjumping(CSP* csp){

    /*
        Tableau permettant la sauvegarde de la variable en cause de l'échec la plus haute
        dans l'arbre de recherche pour chaque iVariable.

        utile pour le backjumping
    */
    int* tabDeepestVariable = createNewTab(csp->nbVariable);
    for(int i=0; i < csp->nbVariable; ++i){
        tabDeepestVariable[i] = csp->nbVariable;
    }

    int checkC; // Variable temporaire prennant le résultat de la fonction checkForConstraint
    int Iposition = 0; // index i de notre matrice de Domaines
    int Jposition = 0;  // index j de notre matrice de Domaines

    while(csp->matrixDomain[0][csp->nbValue-1] != -1){

        printf("[%d][%d]\n", Iposition, Jposition);
        csp->matrixDomain[Iposition][Jposition] = 1;
        checkC = checkForConstraint(csp, Iposition);

        if( checkC < 0 ){ // Contrainte non-violée
            addCheckedValue(csp, Iposition, Jposition);

            // Cas où toutes les variables ne sont pas encore testées
            if( Iposition < csp->nbVariable-1 ){
                ++Iposition;
                Jposition = 0;
            }

            // Cas où toutes les variables ont trouvé au moins une valeurs
            else{
                resetMatrix(csp->matrixDomain, csp->nbVariable, csp->nbValue);
                Iposition = 0;
                Jposition = csp->tabCheckedValue[Iposition];
                csp->matrixDomain[Iposition][Jposition] = -1;

                for(int i=0; i < csp->nbVariable; ++i)
                    tabDeepestVariable[i] = csp->nbVariable;

                ++Jposition;
                printf("\n");
            }
        }

        else{ // Contrainte violée
            if(checkC < tabDeepestVariable[Iposition] ) tabDeepestVariable[Iposition] = checkC;

                // Cas où toutes les valeurs pour une variable ont été testé
                if( Jposition == csp->nbValue-1 ){
                    // Cas où toutes les variables ont été testé
                    if( Iposition == csp->nbVariable-1 ){
                        resetMatrix(csp->matrixDomain, csp->nbVariable, csp->nbValue);
                        for(int i=0; i < tabDeepestVariable[Iposition]; ++i)
                            csp->matrixDomain[i][ csp->tabCheckedValue[i] ] = 1;

                        Iposition = tabDeepestVariable[Iposition];
                        Jposition = csp->tabCheckedValue[Iposition];
                        csp->matrixDomain[Iposition][Jposition] = -1;
                    }

                    // Cas où toutes les variables n'ont pas encore été testé
                    // Simple backtracking
                    else{
                        tabDeepestVariable[Iposition] = csp->nbVariable;
                        csp->matrixDomain[Iposition][Jposition] = -1;

                        while( csp->tabCheckedValue[--Iposition] == csp->nbValue-1 ){
                            Jposition = csp->tabCheckedValue[Iposition];
                            csp->matrixDomain[Iposition][Jposition] = -1;
                            tabDeepestVariable[Iposition] = csp->nbVariable;
                        }

                        Jposition = csp->tabCheckedValue[Iposition];
                        csp->matrixDomain[Iposition][Jposition] = - 1;
                        /*
                        --Iposition;
                        Jposition = csp->tabCheckedValue[Iposition];
                        csp->matrixDomain[Iposition][Jposition] = -1;
                        */
                    }
                }

                ++Jposition;
        }
    }

    free( tabDeepestVariable );
}
