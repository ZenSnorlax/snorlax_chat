#include "Graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef struct Queue{
	int rear;
	int front;
	int *base;
}Queue;
bool visited[MVNum];
Queue que;
void Init(Queue *p){
	p->base = (int *)malloc(MAXSIZE * sizeof(int));
	p->front = 0;
	p->rear = 0;
}
void Enter(Queue * p, int e){
	p->base[p->rear++] = e;
}
void Delete(Queue *p){
	p->front++;
}
int GetFront(Queue *p){
	return p->base[p->front];
}
int Len(Queue *p){
	return p->rear - p->front;
}
void bfs_traverse(AMGraph *G, int v) {
	Enter(&que, v);
	while(Len(&que)) {
		int w = GetFront(&que);
		Delete(&que);
		visited[w] = true;
		printf("访问%c\n", G->vexs[w]);
		for (int j = 0; j < G->vexnum; ++j)
			if(!visited[j] && G->arcs[w][j] < MaxInt)
				Enter(&que, j);
	}
}
void BFS(AMGraph *G){
	for (int v = 0; v < G->vexnum; ++v)
		visited[v] = false;
	for (int v = 0; v < G->vexnum; ++v)
		if(!visited[v])
			bfs_traverse(G, v);
}
int main(int argc, char *argv[])
{
	AMGraph AM;
	Init(&que);
	CreateUDN(&AM);
	BFS(&AM);
	return EXIT_SUCCESS;
}
