#include "common.h"
void createQueue(Queue *que, int n);
void printQueue(Queue *que);
int main(int argc, char *argv[]){
    Queue queue;
    queue_init(&queue);
    createQueue(&queue, 10);
    printQueue(&queue);
    queue_in(&queue, 10);
    printQueue(&queue);
    int value = queue_out(&queue);
    printf("对首元素: %d\n", value);
    printQueue(&queue);
    return 0;
}
void createQueue(Queue *que, int n){
    printf("输入%d个数据: ", n);
    for(int i = 0;i < n; i++){
        int value;
        scanf("%d", &value);
        queue_in(que,value);
    }
}
void printQueue(Queue *que){
    int begin = que->front, end = que->rear;
    printf("打印数据: ");
    while (begin != end) {
    printf("%d ", que->base[begin]);
    begin = (begin + 1) % MAXSIZE;
    }
    printf("\n");
}
