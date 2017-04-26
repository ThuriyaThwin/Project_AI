#include <stdio.h>
#include <stdlib.h>

#include "forwardChecking.h"
#include "matrix.h"
#include "csp.h"


#define IMPOSSIBLE -1
#define VIDE 0
#define AFFECTE 1



void editDomains(CSP *csp, int cas, int iPosition, int jPosition, int value){
    if(cas == 1){
        for(int i = iPosition + 1; i < csp->nbValue; ++i){
            csp->matrixDomain[i][jPosition] = value;
        }
    }
    else if (cas == 2){
        for(int i = iPosition + 1; i < csp->nbValue; ++i){
            int decalage = i -  iPosition;
            csp->matrixDomain[i][jPosition] = value;

            if(jPosition + decalage < csp->nbVariable - 1)
                csp->matrixDomain[i][jPosition + decalage] = value;

            if(jPosition - decalage > 0){
                csp->matrixDomain[i][jPosition - decalage] = value;
            }
        }
    }
    else {
        printf("Erreur de cas");
        exit(-1);
    }
}

/*
    Procédure de forward checking sans heuristique :
*/
void forwardChecking(CSP *csp, int cas) {
    int checkC;
    int i = 0;
    int j = 0;


    while (csp->matrixDomain[0][csp->nbValue - 1] != -1) {

        //sleep(1);
        csp->matrixDomain[i][j] = 1;
        editDomains(csp, cas, i, j, IMPOSSIBLE);

        checkC = checkForConstraint(csp, i);

        if (checkC < 0) { // Contrainte non-violée
            //printf("{ [%d][%d] }\n", Iposition, j);
            addCheckedValue(csp, i, j);

            // Cas où toutes les variables ne sont pas encore testées
            if (i < csp->nbVariable - 1) {
                ++i;
                j = 0;
            }

                // Cas où toutes les variables ont trouvé au moins une valeurs
            else {
                csp->matrixDomain[i][j] = -1;
                /*
                    Solution trouvée, mais tester si possible d'aller encore sur la droite, sinon backtrack
                */
                if (j == csp->nbValue - 1) {
                    --i;
                    // On fait attention à backtrack sur une variable où toutes les valeurs n'ont pas déjà été testées
                    while (i > 0 && csp->tabCheckedValue[i] == csp->nbValue - 1) {
                        j = csp->tabCheckedValue[i];
                        csp->matrixDomain[i][j] = -1;
                        --i;
                    }

                    j = csp->tabCheckedValue[i];
                    csp->matrixDomain[i][j] = -1;
                }

                ++j;
            }
        } else { // Contrainte violée

            // Cas où toutes les valeurs pour une variable ont été testé
            if (j == csp->nbValue - 1) {

                csp->matrixDomain[i][j] = -1;
                editDomains(csp, cas, i, j, VIDE);

                //if( i == csp->nbVariable-1 ){ i = checkC; }
                //else { --i; }
                --i;
                // On fait attention à backtrack sur une variable où toutes les valeurs n'ont pas déjà été testées
                while (i > 0 && csp->tabCheckedValue[i] == csp->nbValue - 1) {
                    j = csp->tabCheckedValue[i];
                    csp->matrixDomain[i][j] = -1;
                    editDomains(csp, cas, i, j, VIDE);
                    --i;
                }

                j = csp->tabCheckedValue[i];
                csp->matrixDomain[i][j] = -1;
                editDomains(csp, cas, i, j, VIDE);
            }

            ++j;
        }
    }
}
