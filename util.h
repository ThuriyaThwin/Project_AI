#ifndef PROJET_IA_UTIL_H
#define PROJET_IA_UTIL_H


// Structure représentant une Pile de Matrice
// Les éléments contenue dans la pile, chacun connaît son prédecesseur dans la Pile
typedef struct Node{
    int** matrix;
    struct Node* next;
} Node;

// La pile elle pointe toujours sur le premier élément : Top
typedef struct Stack{
    struct Node* top;
} Stack;


typedef struct Coords Coords;
struct Coords{
    int x;
    int y;
};

struct Coords findLastModif(int **domaines, int nbPigeons);
void fillColumns(int **domaines, int i, int j, int nbPigeons, int value);

int** createNewMatrix(int row, int col);
int** copyMatrix(int** sourceMatrix, int row, int col);
void resetMatrix(int** matrix, int row, int col);
void printMatrix(int** matrix, int row, int col);
void wipeMatrix(int** matrix, int row);
int checkForConstraintInCol(int** matrix, int number_of_the_col, int nbTotalRow);
int checkForConstraintInRow(int** matrix, int number_of_the_row, int nbTotalCol);
int checkForConstraintInDiagonal(int** matrix, int number_of_the_row, int number_of_the_col, int nbTotalRow, int nbTotalCol);


Stack* initStack();
void wipeStack(Stack* stack, int row);
int** pop(Stack* stack);
int** pop_n_time(Stack* stack, int nTime, int row);
void push(Stack* stack, int** matrix, int row, int col);
void printAllStack(Stack* stack, int row, int col);


#endif //PROJET_IA_UTIL_H
