#ifndef MY_HEADER
#define MY_HEADER
#define MVNum 100
#define MaxInt 32767
typedef char VerTexType;
typedef int ArcType;
//邻接矩阵
typedef struct AMGraph {
	VerTexType vexs[MVNum];
	ArcType arcs[MVNum][MVNum];
	int vexnum, arcnum;
}AMGraph;
//邻接表
typedef struct ArcNode {
	int adjvex;   // 该边所指向的顶点位置
	struct ArcNode *nextarc;//指向下一条边的指针
	char* info;//和边相关的信息
}ArcNode;
typedef struct VNode {
	VerTexType date;
	ArcNode *firstarc;//指向第一条依附该顶点的边的指针
}VNode, AdjList[MVNum];
typedef struct ALGraph {
	AdjList vertices;
	int vexnum, arcnum;
}ALGraph;
//十字链表

#endif // !MY_HEADER

