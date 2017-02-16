#include <stdio.h>
#include <stdlib.h>

#include "generator.h"

int main(int argc, char* argv[]){

    if(argc != 2){
        fprintf(stderr, "Nombre d arguments invalide\n");
        return 1;
    }

    pigeonsGenerator( atoi(argv[1]) );
    return 0;
}
