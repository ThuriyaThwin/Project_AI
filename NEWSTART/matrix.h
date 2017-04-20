#ifndef MATRIX_H
#define MATRIX_H

int* createNewTab(int nbElement);
int** createNewMatrix(int lenDimOne, int lenDimTwo);
void freeMatrix(int** matrix, int lenDimOne);
void resetMatrix(int** matrix, int lenDimOne, int lenDimTwo);
int* copyTab(int* tab, int nbElement);
int** copyMatrix(int** sourceMatrix, int row, int col);
void printTab(int* tab, int nbElement);
void printMatrix(int** matrix, int lenDimOne, int lenDimTwo);

#endif // MATRIX_H
