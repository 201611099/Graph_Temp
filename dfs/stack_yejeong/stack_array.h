#ifndef STACK_ARR_H
# define STACK_ARR_H
#include <stdio.h>
#include <string.h>

#define STACK_MAX 10001

typedef struct _stack {
    int array[STACK_MAX];
    int top;
} Stack;

void init(Stack *sp);

int IsEmpty(Stack *sp);

int size(Stack *sp);

int IsFull(Stack *sp);

void push(Stack *sp, int data);
int pop(Stack *sp);
int peek(Stack *sp);

#endif

// 7, push, 1 ,push ,2, push ,3, pop,empty,size,top //goodgood