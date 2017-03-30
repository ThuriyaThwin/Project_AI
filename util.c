//
// Created by Julien on 16/02/2017.
//

#include <stddef.h>
#include <stdlib.h>
#include "util.h"

int **depiler(Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int **domaine = 0;
    Element *elementDepile = pile->premier;

    if (pile->premier != NULL)
    {
        domaine = elementDepile->domaine;
        pile->premier = elementDepile->suivant;
        free(elementDepile);
    }

    return domaine;
}

void empiler(Pile *pile, int **domaines)
{
    Element *nouveau = malloc(sizeof(*nouveau));
    if (pile == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouveau->domaine = domaines;
    nouveau->suivant = pile->premier;
    pile->premier = nouveau;
}