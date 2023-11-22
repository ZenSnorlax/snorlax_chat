#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef struct TreeNode{
  char date;
  struct TreeNode *l, *r;
}TreeNode, *Tree;
typedef struct Stack{
  char *base, *top;
}Stack;
void InitStack(Stack *stk){
  stk->base = (char *)malloc(MAXSIZE * sizeof(char));
  stk->top = stk->base + MAXSIZE;
}
void InitExpTree(){
  Stack EXRT, OPTR;
  InitStack(&EXRT);
  InitStack(&OPTR);

}
