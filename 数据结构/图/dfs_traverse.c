#include <stdbool.h>
#include <stdio.h>
#include "Graph.h"
//深度遍历
bool visited[MVNum];
void DFS_AM(AMGraph *G, int v){
	printf("%d\n", v);
	visited[v]=true;
	for(int w=0;w<G->vexnum;++w)
		if((G->arcs[v][w]<MaxInt) && (!visited[w]))
			DFS_AM(G, w);

}
void DFS_AL(ALGraph *G, int v){
	printf("%d\n", v);
	visited[v] = true;
	ArcNode *p=G->vertices[v].firstarc;
	while(p!=NULL){
		int w=p->adjvex;
		if((!visited[w]))
			DFS_AL(G, w);
		p=p->nextarc;
	}	
}


