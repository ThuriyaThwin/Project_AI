#include <stdio.h>
#include <stdlib.h>

int backj(){

    // Matrice domaine test
    int** matrixDom = malloc( 4 * sizeof(int*) );
    for(int i=0; i < 4; ++i)
        matrixDom[i] = malloc( 3 * sizeof(int) );

    // Contrôle affichage
    for(int i=0; i < 4; ++i){
        for(int j=0; j < 3; ++j){
            printf("[%d]", matrixDom[i][j]);
        }
        printf("\n");
    }

    for(int i=0; i < 4; ++i){
        free(matrixDom[i]);
    }

    free( matrixDom );

    FILE* txt;
    txt = fopen("config_pigeon.txt", "w");

    // Ligne variable X
    fprintf(txt, "X\n");
    for(int i=0; i < 4; ++i)
        fprintf(txt, "%d ", i);
    fprintf(txt,"\n");

    //Lignes domaines D
    fprintf(txt, "D\n");
    for(int i=0; i < 4; ++i){

        fprintf(txt, "d%d = ", i);
        for(int j=0; j < 3; ++j)
            fprintf(txt, "%d ", j);
        fprintf(txt,"\n");
    }

    //Lignes contraintes C
    fprintf(txt, "C\n");

    for(int i=0; i <4; ++i){
        for(int j= i+1; j < 4; ++j){
            if(i == j) continue;
            fprintf(txt, "(%d, %d)\n", i , j);

            for(int k = 0; k < 3; ++k)
                for(int l = 0; l < 3; ++l) {
                    if(k == l) continue;
                    fprintf(txt, "%d %d\n", k, l);
                }
        }
    }


    return 0;
}
