#ifndef MATRIXTOOLS_H
#define MATRIXTOOLS_H

int* newTab(int nbElement);
int** newMatrix(int lenDimOne, int lenDimTwo);
void freeMatrix(int** matrix, int lenDimOne);
void printTab(int* tab, int nbElement);
void printMatrix(int** matrix, int lenDimOne, int lenDimTwo);

#endif // MATRIXTOOLS_H
