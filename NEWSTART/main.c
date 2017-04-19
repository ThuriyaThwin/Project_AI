#include <stdio.h>
#include <stdlib.h>

#include "backj.h"
#include "pigeon.h"

int main(int argc, char** argv){

    if( argc != 6 ){
        printf("nombre d'arguments incorrect !\n");
        printf("Usage : ./main \n\n[1...*] (nombre de variable)\n1/2 (Pigeon ou Dame)\n1/2 (FC ou BJ)\n1/2 (Normal ou Heuristique)\n0/1 (Rien ou Affiche & Ecriture)\n");
        printf("\n\nEXEMPLE : ./main 10 1 2 1 0\n");
        exit(0);
    }

    CSP* csp;

    // Pigeon
    if(atoi(argv[2]) == 1){

        printf("-> PIGEON\n");

        int nbPigeon = atoi( argv[1] );
        int nbNest = nbPigeon - 1;

        printf("Init CSP : \n");
        csp = pigeonGenerator(nbPigeon, nbNest, atoi(argv[5]));
        printf("OK\n");

        // FC
        if(atoi(argv[3]) == 1){

        }

        // BJ
        if(atoi(argv[3]) == 2){
            printf("--> BACKJUMPING\n");

            // Normal
            if(atoi(argv[4]) == 1){
                printf("---> SANS HEURISTIQUE\n");

                backjumping(csp);

            }

            // Heuristique
            if(atoi(argv[4]) == 2){

            }

            else{
                //erreur
            }

        }

        else{
            //erreur
        }

    }

    // Dame
    if(atoi(argv[2]) == 2){


    }

    else{
        //erreur
    }

    if( atoi(argv[5]) ) printCSP(csp);
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
