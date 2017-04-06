#ifndef PROJET_IA_UTIL_H
#define PROJET_IA_UTIL_H

// Structure pour la deuxième implémentation
typedef struct NodeV2{
    int* tab;
    struct NodeV2* next;
} NodeV2;

typedef struct StackV2{
    struct NodeV2* top;
} StackV2;


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

int* createNewTab(int nbElement);
int* copyTab(int* tab, int nbElement);
void resetTab(int* tab, int row);
void printTab(int* tab, int row);

int** createNewMatrix(int row, int col);
int** copyMatrix(int** sourceMatrix, int row, int col);
void resetMatrix(int** matrix, int row, int col);
void printMatrix(int** matrix, int row, int col);
void wipeMatrix(int** matrix, int row);

int checkForConstraintV2(int* tab, int value, int positionOfValue, int nbTotalRow, int nbTotalCol, int setUp);

int checkForConstraintInCol(int** matrix, int number_of_the_col, int nbTotalRow);
int checkForConstraintInRow(int** matrix, int number_of_the_row, int nbTotalCol);
int checkForConstraintInDiagonal(int** matrix, int number_of_the_row, int number_of_the_col, int nbTotalRow, int nbTotalCol);


Stack* initStack();
StackV2* initStackV2();

void wipeStack(Stack* stack, int row);
void wipeStackV2(StackV2* stack, int row);

int** pop(Stack* stack);
int* popV2(StackV2* stack);

int** pop_n_time(Stack* stack, int nTime, int row);
int* popV2_n_time(StackV2* stack, int nTime);

void push(Stack* stack, int** matrix, int row, int col);
void pushV2(StackV2* stack, int* tab, int row);

void printAllStack(Stack* stack, int row, int col);
void printAllStackV2(StackV2* stack, int row);


#endif //PROJET_IA_UTIL_H
