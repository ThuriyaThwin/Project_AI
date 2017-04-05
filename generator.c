#include <stdio.h>
#include <stdlib.h>
#include "generator.h"
#include "solver.h"

// Génération pour le problème des pigeons
void pigeonsGenerator(int nbPigeons){
    if( nbPigeons <= 0 ){
        fprintf(stderr, "Erreur: nombre de pigeons <= 0\n");
        return;
    }

    int **domaines;

    domaines = malloc(nbPigeons * sizeof(int));
    for(int i = 0; i < nbPigeons; ++i){
        domaines[i] = malloc((nbPigeons - 1) * sizeof(int));
    }

    for(int i = 0; i < nbPigeons; ++i){
        for(int j = 0; j < nbPigeons - 1; ++j){
            domaines[i][j] = 0;
            //printf("%d", domaines[i][j]);
        }
        //printf("\n");
    }

    forwardChecking(domaines, nbPigeons);

/*
    printf("Nombre de pigeons : %d \n", nbPigeons);

    int arrayOne[2][2] = {{1,2},{3,4}};
    int arrayTwo[2][2] = {{5,6},{7,8}};
    int arrayThree[2][2] = {{9,10},{11,12}};
    int arrayFour[2][2] = {{14,15},{16,17}};

    int* arrayP[4][1] = { {*arrayOne}, {*arrayTwo}, {*arrayThree}, {*arrayFour} };

    printf("%d\n", arrayOne[1][1]);

    for(int i=0; i < 4; ++i){
        if( arrayP[i][0] != NULL){

            for(int k=0; k < 2; ++k){
                for(int l=0; l < 2; ++l){

                    printf("arrayP[%d][%d]->array%d[%d][%d] = %d\n", i, 0, i, k, l, *(arrayP[i][0]) + k*2 + l );

                }
            }
        }
    }

    printf("%d\n", *(arrayP[2][0]) + 1*2 + 1);





    //printf("arrayP[0][0] -> arrayOne[0][3] = %d\n", ( *(arrayP[0][0]+1) +1));


    // Création d'un nouveau fichier de configuration pour les pigeons
    FILE* txt;
    txt = fopen("config_pigeon.txt", "w");
    // Ligne variable X
    fprintf(txt, "X\n");
    for(int i=0; i < nbPigeons; ++i)
        fprintf(txt, "%d ", i);
    fprintf(txt,"\n");

    //Lignes domaines D
    fprintf(txt, "D\n");
    for(int i=0; i < (nbPigeons); ++i){

        fprintf(txt, "d%d = ", i);
        for(int j=0; j < (nbPigeons-1); ++j)
            fprintf(txt, "%d ", j);
        fprintf(txt,"\n");
    }

    //Lignes contraintes C
    fprintf(txt, "C\n");

    for(int i=0; i < nbPigeons; ++i){
        for(int j= i+1; j < nbPigeons; ++j){
            if(i == j) continue;
            fprintf(txt, "(%d, %d)\n", i , j);

            for(int k = 0; k < nbPigeons - 1; ++k)
                for(int l = 0; l < nbPigeons - 1; ++l) {
                    if(k == l) continue;
                    fprintf(txt, "%d %d\n", k, l);
                }
        }
    }*/
}


// Génération pour le problème des dames
void checkersGenerator(unsigned long nbCheckers){

}
