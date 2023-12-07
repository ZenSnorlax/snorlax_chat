#ifndef HEADER
#define HEADER
#define MVNum 100
#define MaxInt 32765
typedef char VerTexType;
typedef int ArcType;
typedef struct AMGraph{
	VerTexType vexs[MVNum];
	ArcType arcs[MVNum][MVNum];
	int vexnum, arcnum;
}AMGraph;
void CreateUDN(AMGraph *G);
#endif // !HEADER
