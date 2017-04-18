#include <stdio.h>
#include <stdlib.h>

#include "pigeon.h"

int main(){

    CSP* csp = pigeonGenerator(4, 3);
    printCSP(csp);
    freeCSP(csp);

    /*
        EXEMPLE fonctionnement CSP contrainte + tuples

        int** subArray = malloc( sizeof(int*) * 2 );
        subArray[0] = malloc( sizeof(int) * 2 );
        subArray[1] = malloc( sizeof(int) * 2 );

        subArray[0][0] = 3;
        subArray[0][1] = 2;
        subArray[1][0] = 1;
        subArray[1][1] = 0;

        int**** mainArray = malloc( sizeof(int***) * 2 );
        mainArray[0] = malloc( sizeof(int**) * 2 );
        mainArray[1] = malloc( sizeof(int**) * 2 );

        mainArray[0][0] = subArray;

        printf("%d\n", mainArray[0][0][0][0]);
        printf("%d\n", mainArray[0][0][0][1]);
        printf("%d\n", mainArray[0][0][1][0]);
        printf("%d\n", mainArray[0][0][1][1]);

    */


    return 0;
}
