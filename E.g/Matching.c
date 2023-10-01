#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define OK 1
#define true 1
#define false 0
#define OVERFLOW -1
typedef int bool;
typedef int Status;
typedef struct mystack{
char *base;
char* top;
int length;
}Stack;
Status Stack_Init(Stack* stack,int len){
    stack->base=(Stack*)malloc(sizeof(Stack)*len);
    if(!stack->base) exit(OVERFLOW);
    stack->top=stack->base;
    stack->length=len;
    return OK;
}
char Stack_pop(Stack* stack){
    if(stack->base==stack->top) exit(OVERFLOW);
    return *--stack->top;    
}
Status Stack_push(Stack* stack,char e){
    if(stack->top-stack->base==stack->length) exit(OVERFLOW);
    *stack->top++=e;
    return OK;
}
bool Stack_empty(Stack* stack){
    if(stack->base==stack->top) return true;
    return false;
}
char Stack_get(Stack* stack){
    if(stack->base!=stack->top) return *(stack->top-1);
}
char pairs(char a){
    if(a=='}')return '{';
    if(a==']')return '[';
    if(a=='(')return '(';
    return 0;
}
bool Matching(char* s){
    int n=strlen(s);
    if(n%2==1) return false;
    Stack sk;
    Stack_Init(&sk,n);
    for(int i=0;i<n;++i){
        char ch=pairs(s[i]);
        if(ch){
            if(Stack_empty(&sk)||Stack_get(&sk)!=ch){
                return false;
            }
            Stack_pop(&sk);
        }
        else {
            Stack_push(&sk,s[i]);
        }
    }
    return sk.base==sk.top;
    return false;
}
int main(){
}