#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generator.h"
#include "solver.h"
#include "backjumping.h"

// Génération pour le problème des pigeons
void pigeonsGenerator(int nbPigeons){
    if( nbPigeons <= 1 ){
        fprintf(stderr, "Erreur: nombre de pigeons <= 1\n");
        return;
    }

    char c[1];
    do{
        printf("Afficher matrice ? 0(Non) - 1(Oui)\n");
        scanf("%s", c);
    } while( strcmp(c,"1") != 0 && strcmp(c,"0") != 0 );

    int tmp = atoi(c);


    do{
        printf("BJ(0) - FC(1)\n");
        scanf("%s", c);
    } while( strcmp(c,"0") != 0 && strcmp(c,"1") != 0 );

    if( strcmp(c,"0") == 0 ) {
        backjumpingPigeons(nbPigeons, nbPigeons - 1, tmp);
    }
    else {
        printf("FC");
        int **domaines;

        domaines = malloc(nbPigeons * sizeof(int));
        for (int i = 0; i < nbPigeons; ++i) {
            domaines[i] = malloc((nbPigeons - 1) * sizeof(int));
        }

        for (int i = 0; i < nbPigeons; ++i) {
            for (int j = 0; j < nbPigeons - 1; ++j) {
                domaines[i][j] = 0;
            }
        }
        forwardChecking(domaines, nbPigeons);
    }


    /*// Création d'un nouveau fichier de configuration pour les pigeons
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
void checkersGenerator(int nbCheckers){
    if( nbCheckers <= 1 ){
        fprintf(stderr, "Erreur: nombre de pigeons <= 1\n");
        return;
    }

    char c[1];
    do{
        printf("Afficher matrice ? 0(Non) - 1(Oui)\n");
        scanf("%s", c);
    } while( strcmp(c,"1") != 0 && strcmp(c,"0") != 0 );

    int tmp = atoi(c);
    backjumpingCheckers(nbCheckers, nbCheckers, tmp);
}