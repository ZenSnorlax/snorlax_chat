#include <stdio.h>
#include <stdlib.h>
#define OVERFLOW 1
typedef struct StackNode{
    int date;
    struct StackNode *next;
}StackNode;
void stack_link_init(StackNode **pstk){
    *pstk = NULL;
}
void stack_link_push(StackNode **pstk, int e){
    StackNode *p = (StackNode *)malloc(sizeof(StackNode));
    p->date = e;
    p->next = *pstk;
    *pstk = p;
}
int stack_link_pop(StackNode **stk){
    if (*stk == NULL) exit(OVERFLOW);
    StackNode *p = *stk;
    *stk = (*stk)->next;
    return p->date;
}
void printStack_link(StackNode *stk){
    StackNode *p = stk;
    printf("打印数据: ");
    while(p){
        printf("%d ",p->date);
        p=p->next;
    }
    printf("\n");
}
int main(int argc, char *argv[]){
    StackNode *stk;
    stack_link_init(&stk);
    int value = stack_link_pop(&stk);
    printf("栈顶元素: %d\n", value);
    printStack_link(stk);
    return 0;
}