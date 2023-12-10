#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
#define OVERFLOW 1
//定义顺序栈
typedef struct  Stack{
	int *top;
	int *base;
}Stack;
//定义顺序队列
typedef struct Queue{
	int front;
	int rear;
	int *base; //基地址
}Queue;
//初始化栈
void stack_init(Stack *stk){
	stk->base = (int *)malloc(sizeof(int) * MAXSIZE);
	if (!stk->base) exit(OVERFLOW);
	stk->top = stk->base;
}
//入栈
void stack_push(Stack *stk, int e){
	if (stk->top - stk->base == MAXSIZE) exit(OVERFLOW);
	*stk->top++ = e;
}
//出栈
int stack_pop(Stack *stk){
	if(stk->base ==stk->top) exit( OVERFLOW);
	return *--stk->top;
}
//初始化队列
void queue_init(Queue *que){
	que->base = (int *)malloc(sizeof(int) * MAXSIZE);
	que->front = 0;
	que->rear = 0;
}
//入队
void queue_in(Queue *que, int e){
	if (que->front == (que->rear + 1) % MAXSIZE) exit(OVERFLOW);
	que->base[que->rear] = e;
	que->rear = (que->rear + 1)%MAXSIZE;
}
//出队
int queue_out(Queue *que){
	if (que->front == que->rear) exit(OVERFLOW);
	int e = que->base[que->front];
	que->front = (que->front + 1) % MAXSIZE;
	return e;
}
//求长
int queue_len(Queue *que){
	return que->front - que->rear;
}


