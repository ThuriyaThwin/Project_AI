#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generator.h"
#include "solver.h"

int main(int argc, char* argv[]){

    if(argc != 2){
        fprintf(stderr, "Nombre d arguments invalide\n");
        return 1;
    }

    char c[1];
    do{
        printf("Pigeons(0) - Dames(1)\n");
        scanf("%s", c);
    } while( strcmp(c,"0") != 0 && strcmp(c,"1") != 0 );

    if( strcmp(c,"0") == 0 ) pigeonsGenerator( atoi(argv[1]) );
    else checkersGenerator( atoi(argv[1]) );

    return 0;
}
