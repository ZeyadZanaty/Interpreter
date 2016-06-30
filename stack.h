#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#define TYPE float
#define MAX_SIZE 100

typedef struct {
    int top;
    TYPE items [MAX_SIZE];
}Stack;

void initialize(Stack *s)
{
    s->top = -1;
}
int size (Stack *s)
{
    return s->top + 1;
}
int isFull(Stack *s)
{
    if (size (s) == MAX_SIZE)
        return 1;
    else
        return 0;
}
int isEmpty(Stack *s)
{
    if (size (s) == 0)
        return 1;
    else
        return 0;
}
void push (TYPE value, Stack *s)
{
    if (!isFull(s)){
        s->top += 1;
        s->items[s->top] = value;
    }
    else
        printf("\nError\n The stack is full!\n");
}
TYPE peak(Stack *s)
{
    if (!isEmpty(s)){
        return s->items[s->top];
    }
    else {
       // printf("\nThe stack is Empty !");
        return -1;
    }
}
TYPE pop(Stack *s)
{
    if (!isEmpty(s)){
        TYPE value = s->items[s->top];
        s->top -= 1;
        return value;
    }
    else {
        return -1; //error
       // printf("\nThe stack is Empty!");
    }
}

#endif // STACK_H_INCLUDED
