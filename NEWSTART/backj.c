#include <stdio.h>
#include <stdlib.h>

#include "backj.h"
#include "matrix.h"

void backjumping(CSP* csp){
    int** matrixViolatedConstraint = createNewMatrix(csp->nbVariable, csp->nbValue);
    int Iposition = 0;
    int Jposition = 0;

    while(csp->matrixDomain[0][csp->nbValue-1] != -1){
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
    
    freeMatrix(matrixViolatedConstraint, csp->nbValue);
}
