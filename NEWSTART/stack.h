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



typedef struct NodeInt{
    int var;
    struct NodeInt* next;
} NodeInt;

typedef struct StackInt{
    struct NodeInt* top;
} StackInt;

StackInt* initStackInt();
void pushInt(StackInt* stack, int val);
int popInt(StackInt* stack);

#endif // STACK_H
