#include "Graph.h"
#include <stdbool.h>
#include <stdio.h>
bool visited[MVNum];
void dfs_traverse(const AMGraph *G, const int v) {
    printf("访问%c\n", G->vexs[v]);
    visited[v] = true;
    for (int i = 0; i < G->vexnum; ++i)
        if (!visited[i] && G->arcs[v][i] < MaxInt)
            dfs_traverse(G, i);
}
void DFS(AMGraph *G) {
    for (int v = 0; v < G->vexnum; ++v)
        visited[v] = false;
    for (int v = 0; v < G->vexnum; ++v)
        if (!visited[v])
            dfs_traverse(G, v);
}
int main() {
    AMGraph AG;
    CreateUDN(&AG);
    DFS(&AG);
    return 0;
}
