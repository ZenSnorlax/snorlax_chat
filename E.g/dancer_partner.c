#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -1
#define MAXSIZE 100
#define TRUE 1
#define ERROR 0
typedef int Status;
typedef struct Person_message {
 char name[20];
 char sex;
 }Person;
typedef struct myqueue{
    int rear;
    int front;
    Person* base;    
}Queue;
//初始化
Status InitQueue(Queue* queue){
   queue->base=(Person*)malloc(MAXSIZE*sizeof(Person));
   if(!queue->base) exit(OVERFLOW);
   queue->rear=queue->front=0;
   return TRUE;
}
//入队
Status EnQueue(Queue* queue,Person* e){
   if((queue->rear+1)%MAXSIZE==queue->front) return ERROR;
    queue->base[queue->rear]=e;
    queue->rear=(queue->rear+1)%MAXSIZE;
    return TRUE;
}
//出队
Status DeQueue(Queue* queue,Person* e){
    if(queue->rear==queue->front)   return ERROR;
    *e=queue->base[queue->front];
    queue->front=(queue->front+1)%MAXSIZE;
    return TRUE;
    }
//读取队首
Person GetHead(Queue* queue){
    if(queue->front!=queue->rear) return queue->base[queue->front];
}
//判空
Status QueueEmpty(Queue* queue){
    if(queue->front==queue->rear)   return TRUE;
    return ERROR;
}
//实现
void dancer_partner(Person dancer[],int num){
    Queue *Mdancers;//定义
    Queue *Fdancers;
    Person p;
    InitQueue(Mdancers);//初始化
    InitQueue(Fdancers);
    for(int i=0;i<num;++i){//入队
       Person p=dancer[i];
        if(p.sex=='M') EnQueue(&Mdancers,&p);
        else EnQueue(&Fdancers,&p);
    }
    printf("The dancing partners are:\n");
    while(!QueueEmpty(Mdancers)&&!QueueEmpty(Fdancers)){
        DeQueue(Mdancers,&p);//男士出队
        printf("%s ",p.name);
        DeQueue(Fdancers,&p);//女士出队
        printf("%s\n",p.name);
    }
    if(!QueueEmpty(Mdancers)){
        p=GetHead(Mdancers);
        printf("%s\n",p.name);
    }
    if(!QueueEmpty(Fdancers)){
        p=GetHead(Fdancers);
        printf("%s\n",p.name);
    }
}
int main(){

}