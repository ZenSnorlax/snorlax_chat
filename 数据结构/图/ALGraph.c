#include"Graph.h"
#include <stdlib.h>
#include <stdio.h>
//定位
int LocateVex(const ALGraph* G, const char value) {
    for (int i = 0; i < G->vexnum; ++i)
        if (value == G->vertices[i].date)
            return i;
    return -1;
}
//创造无向图
void CreateUDN(ALGraph *G){
	scanf("%d%d", &G->vexnum, &G->arcnum);//输入总顶点数, 总边数
	getchar();//吸收换行
	for (int i=0;i<G->vexnum;++i) {
		G->vertices[i].date = getchar();
		G->vertices[i].firstarc=NULL;
	}
	getchar();//吸收换行
	for (int k=0;k<G->arcnum;++k) {
		const VerTexType v1=getchar();
		const VerTexType v2=getchar();
		getchar();//吸收换行
		const int i=LocateVex(G, v1);
		const int j=LocateVex(G, v2);
		ArcNode *p1=(ArcNode *)malloc(sizeof(ArcNode));
		p1->adjvex=j;
		p1->nextarc = G->vertices[i].firstarc;
		G->vertices[i].firstarc=p1;
		ArcNode *p2=(ArcNode *)malloc(sizeof(ArcNode));
		p2->adjvex=i;
		p2->nextarc=G->vertices[j].firstarc;
		G->vertices[j].firstarc=p2;

		}
}
//创造有向图
void CreateDN(ALGraph *G){
	scanf("%d%d", &G->vexnum, &G->arcnum);
	getchar();
	for(int i=0;i<G->vexnum;++i){
		G->vertices[i].date=getchar();
		G->vertices[i].firstarc= NULL;
	}
	getchar();
	for(int k=0;k<G->arcnum;++k){
		const VerTexType v1=getchar();
		const VerTexType v2=getchar();
		getchar();
		const int i=LocateVex(G, v1);
		const int j=LocateVex(G, v2);
		ArcNode *p1=(ArcNode *)malloc(sizeof(ArcNode));
		p1->adjvex=j;
		p1->nextarc=G->vertices[i].firstarc;
		G->vertices[i].firstarc=p1;
	}
}
