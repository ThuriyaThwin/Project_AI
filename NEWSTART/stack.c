#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "matrix.h"

Stack* initStack(){
    Stack* stack = malloc(sizeof( *stack ));
    stack->top = NULL;

    return stack;
}

void push(Stack* stack, int* tab, int row){
    Node* newTop = malloc( sizeof( *newTop ));
    if( stack == NULL || newTop == NULL ){
        printf("Erreur : stack or newTop NULL.\n");
        exit(-1);
    }

    newTop->tab = copyTab(tab, row);
    newTop->next = stack->top;
    stack->top = newTop;
}

int* pop(Stack* stack){
    int* tmpTab;

    if( stack->top != NULL ){
        tmpTab = stack->top->tab;
        Node* node = stack->top;
        stack->top = stack->top->next;
        free(node);
    }
    else{
        printf("Erreur : top NULL.\n");
        exit(-1);
    }

    return tmpTab;
}


int* pop_n_time(Stack* stack, int nTime){
    for(int i=0; i < nTime-1; ++i){
        free(pop(stack));
    }

    return pop(stack);
}

void wipeStack(Stack* stack, int row){
    while( stack->top != NULL){
        free(stack->top->tab);
        Node* top = stack->top;
        stack->top = stack->top->next;
        free(top);
    }

    free(stack);
}

void printAllStack(Stack* stack, int row){
    Node* index = stack->top;

    printf("-- AFFICHAGE PILE --\n");
    while( index != NULL ){
        printTab(index->tab, row);
        index = index->next;
    }
    printf(" -- FOND DE PILE --\n");
}
