#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
#define OVERFLOW 1
typedef struct  Stack{
    int *top;
    int *base;
    int len;
}Stack;
void stack_init(Stack *stk){
    stk->base = (int *)malloc(sizeof(int) * MAXSIZE);
    if (!stk->base) exit(OVERFLOW);
    stk->len = MAXSIZE;
    stk->top = stk->base;
}
void stack_push(Stack *stk, int e){
    if (stk->top - stk->base == stk->len) exit(OVERFLOW);
    *stk->top++ = e;
}
int stack_pop(Stack *stk){
    return *--stk->top;
}
