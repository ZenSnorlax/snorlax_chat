#include <stdio.h>
#include "Graph.h"
int LocateVex(AMGraph *G, VerTexType value){
for(int i=0;i<G->vexnum;++i)
	if(G->vexs[i]==value)
		return i;
return -1;
}
//无向图
void CreateUDN(AMGraph *G){
scanf("%d%d", &G->vexnum, &G->arcnum) ;
for(int i=0;i<G->vexnum;++i)
	for(int j=0;j<G->vexnum;++j)
		G->arcs[i][j]=MaxInt;
for(int k=0;k<G->arcnum;++k){
const VerTexType v1 = getchar();
const VerTexType v2 = getchar();
getchar();
int weight;
scanf("%d", &weight);
getchar();
const int i=LocateVex(G, v1);
const int j=LocateVex(G, v2);
G->arcs[i][j]=weight;
G->arcs[j][i]=weight;
}
}
//有向图
void CreateDN(AMGraph *G){
scanf("%d%d", &G->vexnum, &G->arcnum);
for(int i=0;i<G->vexnum;++i)
	for(int j=0;j<G->vexnum;++j)
		G->arcs[i][j]=MaxInt;
for(int k=0;k<G->arcnum;++k){
const VerTexType v1 = getchar();
const VerTexType v2 = getchar();
getchar();
int weight;
scanf("%d", &weight);
getchar();
const int i=LocateVex(G, v1);
const int j=LocateVex(G, v2);
G->arcs[i][j]=weight;
}
}

