#ifndef STACK_H
#define STACK_H

typedef struct Node{
    int* tab;
    struct Node* next;
} Node;

typedef struct Stack{
    struct Node* top;
} Stack;

Stack* initStack();
void push(Stack* stack, int* tab, int row);
int* pop(Stack* stack);
int* pop_n_time(Stack* stack, int nTime);
void wipeStack(Stack* stack, int row);
void printAllStack(Stack* stack, int row);

#endif // STACK_H
