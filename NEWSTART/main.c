#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "backj.h"
#include "pigeon.h"
#include "dame.h"
#include "forwardChecking.h"
#include "forwardCheckingHeuristic.h"

CSP* csp;

int main(int argc, char** argv){

    if( argc != 6 ){
        printf("nombre d'arguments incorrect !\n");
        printf("Usage : ./main \n\n[1...*] (nombre de variable)\n1/2 (Pigeon ou Dame)\n1/2 (FC ou BJ)\n1/2 (Normal ou Heuristique)\n0/1 (Ecriture ou Non du fichier)\n");
        printf("\n\nEXEMPLE : ./main 10 1 2 1 0\n");
        exit(0);
    }

    if( atoi(argv[1]) < 2 ){
        printf("Erreur : nombre de variable à traiter insuffisant.\n");
        exit(0);
    }

    clock_t begin = clock();

    // Pigeon
    if(atoi(argv[2]) == 1){
        printf("-> PIGEON\n");
        int nbPigeon = atoi( argv[1] );

        printf("Init CSP : \n");
        csp = pigeonGenerator(nbPigeon, atoi(argv[5]));
        printf("OK\n");

        if(atoi(argv[3]) == 1){ // FC
            printf("--> FORWARD CHECKING\n");
            if(atoi(argv[4]) == 1){ // Normal
                printf("---> SANS HEURISTIQUE\n");
                forwardChecking(csp, 1);
            }
            else if(atoi(argv[4]) == 2){ // Heuristique
                forwardCheckingH(csp, 2);
            }
        }
        if(atoi(argv[3]) == 2){ // BJ
            printf("--> BACKJUMPING\n");
            if(atoi(argv[4]) == 1){ // Normal
                printf("---> SANS HEURISTIQUE\n");
                backjumping(csp);
            }
            else if(atoi(argv[4]) == 2){ // Heuristique
                printf("---> AVEC HEURISTIQUE MC\n");
                backjumpingMaximumConstraint(csp);
            }
        }
    }
    // Dame
    else if(atoi(argv[2]) == 2){
        printf("-> DAME\n");
        int nbDame = atoi( argv[1] );
        printf("Init CSP : \n");
        csp = dameGenerator(nbDame, atoi(argv[5]));
        printf("OK\n");
        if(atoi(argv[3]) == 1){ // FC
            printf("--> FORWARD CHECKING\n");
            if(atoi(argv[4]) == 1){ // Normal
                printf("---> SANS HEURISTIQUE\n");
                forwardChecking(csp, 2);
            }
            if(atoi(argv[4]) == 2){ // Heuristique
                forwardCheckingH(csp, 2);
            }
        }

        else if(atoi(argv[3]) == 2){ // BJ
            printf("--> BACKJUMPING\n");
            if(atoi(argv[4]) == 1){ // Normal
                printf("---> SANS HEURISTIQUE\n");
                backjumping(csp);
            }
            else if(atoi(argv[4]) == 2){ // Heuristique
                printf("---> AVEC HEURISTIQUE MC\n");
                backjumpingMaximumConstraint(csp);
            }
        }
    }

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\n++++ RESULTAT(S) ++++\n");
    if( atoi(argv[5] ) ) printAllStack(csp->results, csp->nbVariable);
    printf("\n\n%d solution(s) trouvée(s) :\n", csp->nbResult);
    printf("TEMPS EXECUTION CPU : %lf secondes.\n", time_spent);

    freeCSP(csp, atoi(argv[2]));

    return 0;
}
