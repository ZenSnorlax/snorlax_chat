#include"Graph.h"
#include <stdio.h>
struct closedge{
	VerTexType adjvex;	//最小边在U上的那个顶点
	ArcType lowcost;	//最小边上的权值
}closedge[MVNum];
int LocateVex(AMGraph *G, VerTexType ch){
	for (int i = 0; i < G->vexnum; ++i)
		if(G->vexs[i] == ch)
			return i;
	return -1;
}
int Min(AMGraph *G){
	int index;
	int min = MaxInt;
	for (int i = 0; i < G->vexnum; ++i){
		if (!closedge[i].lowcost)
			continue;
		if (min > closedge[i].lowcost){
			min = closedge[i].lowcost;
			index = i;
		}

	}
	return index;
}
void MiniSpanTree_Prim(AMGraph *G, VerTexType u){
	int k = LocateVex(G, u);
	for (int j = 0; j < G->vexnum; ++j)
		if(j != k){
			closedge[j].adjvex = u;
			closedge[j].lowcost = G->arcs[k][j];
		}
	closedge[k].lowcost = 0;
	for (int i = 1; i < G->vexnum; ++i){
		int m = Min(G);
		VerTexType u0 = closedge[m].adjvex;
		VerTexType v0 = G->vexs[m];
		printf("%c %c\n", u0, v0);
		closedge[m].lowcost = 0;
		for (int j = 0; j < G->vexnum; ++j)
			if (G->arcs[m][i] < closedge[j].lowcost){
				closedge[j].adjvex = G->vexs[m];
				closedge[j].lowcost = G->arcs[m][j];
			}
	}

}
int main(){
	AMGraph AG;
	CreateUDN(&AG);
	MiniSpanTree_Prim(&AG, 'a');
	return 0;
}

