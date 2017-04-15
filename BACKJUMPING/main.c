#include <stdio.h>
#include <stdlib.h>

#include "pigeon.h"

int main(){

    CSP* csp = pigeonGenerator(3, 2);

    //printCSP(csp, 10, 9);
    freeCSP(csp, 3, 2);

    return 0;
}
