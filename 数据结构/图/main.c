#include<stdio.h>
#define MVNum 100
#define MaxInt 32767

typedef enum {
    UDN,
    DN
} GraphType;

typedef enum {
    false,
    true
} bool;

typedef char VerTexType;
typedef int ArcType;

typedef struct AMGraph{
    VerTexType vexs[MVNum];
    ArcType arcs[MVNum][MVNum];
    int vexnum, arcnum;
} AMGraph;

//定位
int LocateVex(const AMGraph* G, const char value) {
    for (int i = 0; i < G->vexnum; ++i)
        if (value == G->vexs[i])
            return i;
    return -1;
}

//初始化
void Init(AMGraph* G) {
    scanf("%d%d", &G->vexnum, &G->arcnum); //输入顶点数, 边数
    for (int i = 0; i < G->vexnum; ++i)
        G->vexs[i] = getchar();
    getchar(); //吸收换行
    for (int i = 0; i < G->vexnum; ++i)
        for (int j = 0; j < G->vexnum; ++j)
            G->arcs[i][j] = MaxInt;
}

//输入顶点以及边
void Input(AMGraph* G, const GraphType graphtype) {
    const char v1 = getchar();
    const char v2 = getchar();
    getchar(); //吸收换行
    int weight;
    scanf("%d", &weight);
    getchar(); //吸收换行
    const int i = LocateVex(G, v1);
    const int j = LocateVex(G, v2);
    G->arcs[i][j] = weight;
    if (graphtype == UDN)
        G->arcs[j][i] = weight;
}

//创造无向图
void CreateUDN(AMGraph* G) {
    Init(G);
    for (int i = 0; i < G->arcnum; ++i)
        Input(G, UDN);
}

//创造有向图
void CreateDN(AMGraph* G) {
    Init(G);
    for (int i = 0; i < G->arcnum; ++i)
        Input(G, DN);
    for (int j = 0; j < G->arcnum; ++j)
        Input(G, DN);
}

//Dijkstra
void ShortestPath_DIJ(const AMGraph* G, const int v0) {
    const int n = G->vexnum;
    bool S[n];
    int Path[n];
    int D[n];

    for (int v = 0; v < n; ++v) {
        S[v] = false;
        D[v] = G->arcs[v0][v];
        if (D[v] < MaxInt) Path[v] = v0;
        else Path[v] = -1;
    }
    S[v0] = true;
    D[v0] = 0;
    //初始化结束
    for (int i = 1; i < n; ++i) {
        int v = -1;
        int min = MaxInt;
        for (int w = 0; w < n; ++w)
            if (!S[w] && D[w] < min) {
                v = w;
                min = D[w];
            }
        S[v] = true;
        for (int w = 0; w < n; ++w)
            if (!S[w] && (D[v] + G->arcs[v][w]) < D[w]) {
                D[w] = D[v] + G->arcs[v][w];
                Path[w] = v;
            }
    }
}

//Floyd
void ShortestPath_Floyd(const AMGraph* G) {
    int n = G->vexnum;
    int Path[n][n];
    int D[n][n];
    //初始化
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            D[i][j] = G->arcs[i][j];
            if (D[i][j] < MaxInt && i != j)
                Path[i][j] = i;
            else Path[i][j] = -1;
        }
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (D[i][k] + D[k][j] < D[i][j]) {
			                    D[i][j] = D[i][k] + D[k][j];
                    Path[i][j] = Path[k][j];
                }
}

int main() {
    return 0;
}

