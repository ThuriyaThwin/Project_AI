#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "backj.h"
#include "pigeon.h"
#include "dame.h"

int main(int argc, char** argv){

    if( argc != 6 ){
        printf("nombre d'arguments incorrect !\n");
        printf("Usage : ./main \n\n[1...*] (nombre de variable)\n1/2 (Pigeon ou Dame)\n1/2 (FC ou BJ)\n1/2 (Normal ou Heuristique)\n0/1 (Ecriture ou Non du fichier)\n");
        printf("\n\nEXEMPLE : ./main 10 1 2 1 0\n");
        exit(0);
    }

    clock_t begin = clock();
    CSP* csp;

    // Pigeon
    if(atoi(argv[2]) == 1){
        printf("-> PIGEON\n");
        int nbPigeon = atoi( argv[1] );

        printf("Init CSP : \n");
        csp = pigeonGenerator(nbPigeon, atoi(argv[5]));
        printf("OK\n");

        if(atoi(argv[3]) == 1){ // FC

        }
        if(atoi(argv[3]) == 2){ // BJ
            printf("--> BACKJUMPING\n");
            if(atoi(argv[4]) == 1){ // Normal
                printf("---> SANS HEURISTIQUE\n");
                backjumping(csp);
            }
            if(atoi(argv[4]) == 2){ // Heuristique

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
        printf("-> DAME\n");
        int nbDame = atoi( argv[1] );
        printf("Init CSP : \n");
        csp = dameGenerator(nbDame, atoi(argv[5]));
        printf("OK\n");
        if(atoi(argv[3]) == 1){ // FC

        }
        if(atoi(argv[3]) == 2){ // BJ
            printf("--> BACKJUMPING\n");
            if(atoi(argv[4]) == 1){ // Normal
                printf("---> SANS HEURISTIQUE\n");
                backjumping(csp);
            }
            if(atoi(argv[4]) == 2){ // Heuristique

            }
            else{
                //erreur
            }
        }
        else{
            //erreur
        }
    }
    else{
        //erreur
    }

    //if( atoi(argv[5]) ) printCSP(csp);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\n++++ RESULTAT(S) ++++\n");
    printAllStack(csp->results, csp->nbVariable);
    printf("\n\n%d solution(s) trouvée(s) :\n", csp->nbResult);
    printf("TEMPS EXECUTION CPU : %lf secondes.\n", time_spent);

    freeCSP(csp, atoi(argv[2]));

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
