#include "Graph.h"
#include <stdio.h>
#include <stdbool.h>
bool visited[MVNum];
void dfs_traverse(const AMGraph *G, const int v) {
	printf("访问%c\n", G->vexs[v]);
	visited[v] = true;
	for (int i = 0; i < G->vexnum; ++i)
		if(!visited[i] && G->arcs[v][i] < MaxInt)
			dfs_traverse(G, i);

}
int main() {
	AMGraph AG;
	for (int i = 0; i < AG.vexnum; ++i)
		visited[i] = false;
	CreateUDN(&AG);
	dfs_traverse(&AG, 0);
}
