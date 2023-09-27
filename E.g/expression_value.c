#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
#define OVERFLOW -1
#define ERROR 0
#define TRUE 1
typedef char ElemType;
typedef int Status;
typedef struct mystack{
ElemType* base;
ElemType* top;
int length;    
}Stack;
//初始化栈
Status InitStack(Stack* stack){
    stack->base=(ElemType*)malloc(MAXSIZE*sizeof(ElemType));
    if(!stack->base)    exit(OVERFLOW);
    stack->length=MAXSIZE;
    stack->top=stack->base;
    return TRUE;
}
//入栈
Status Push(Stack* stack,ElemType* e){
    if(stack->top-stack->base==stack->length) return ERROR;
    *stack->top++=*e;
    return TRUE;
}
//出栈
Status Pop(Stack *stack,ElemType* e){
    if(stack->top==stack->base) return ERROR;
    *e=*--stack->top;
    return TRUE;
}
//读取栈顶
ElemType GetTop(Stack* stack){
    if(stack->top!=stack->base) return *stack->top;
}
//优先级比较
char Precede(char a,char b){
   
   }  
ElemType expression_value()
{
    Stack* OPND;Stack* OPTR;
    ElemType ch;
    ElemType a,b;
    char theta,x;
    Initstack(OPND);
    Initstack(OPTR);
    push(OPTR,'#');
    ch=getchar();
    while(ch!='#'||GetTop(OPTR)!='#')   
    {
        if(!In(ch)) {Push(OPND,ch);ch=getchar();}
        else
        switch(Precede(GetTop(OPTR),ch)){
            case '<':
            Push(OPTR,&ch);ch=getchar();break;
            case '>':
            Pop(OPTR,&theta);Pop(OPND,b);Pop(OPND,a);
            push(OPND,Operate(a,theta,b));break;
            case '=':
            Pop(OPTR,&x);ch=getchar();break;
        }
    }
    return GetTop(OPND);
}
int main(){

}


