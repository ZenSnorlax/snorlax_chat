#include "common.h"
void createStack(Stack *stk, int n);
void printStack(Stack *stk);
int main(int argc, char *argv[]){
    Stack stack;
    stack_init(&stack);
    createStack(&stack, 10);
    printStack(&stack);
    stack_push(&stack, 10);
    printStack(&stack);
    int value = stack_pop(&stack);
    printf("出栈元素: %d\n", value);
    printStack(&stack);
    return 0;
}
void createStack(Stack *stk, int n){
    printf("输入%d个数据: ", n);
    for(int i = 0; i < n; i++){
        int e;
        scanf("%d", &e);
        stack_push(stk, e);
    }
}
void printStack(Stack *stk){
    printf("打印栈内元素: ");
    for(int *i = stk->top; i != stk->base; i--){
        printf("%d ", *(i-1));
    }
    printf("\n");
}