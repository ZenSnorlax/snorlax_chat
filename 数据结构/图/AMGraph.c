#include "Graph.h"
#include <stdio.h>
int Locate(const VerTexType ch, AMGraph *G) {
	int i;
	for (i = 0; G->vexs[i] != '\0' && i < G->vexnum; ++i)
		if (ch == G->vexs[i])
			return i;
	G->vexs[i] = ch;
	return i;
}
void CreateUDN(AMGraph *G){
	printf("请输入顶点数:");
	scanf("%d", &G->vexnum);
	getchar();	//吸收回车 
	printf("请输入边数:");
	scanf("%d", &G->arcnum);
	getchar();	//吸收回车
			//初始化
	for(int i = 0; i < G->vexnum; ++i){
		G->vexs[i] = '\0';
		for(int j = 0; j < G->vexnum; ++j)
			G->arcs[i][j] = MaxInt;
	}
	for(int k = 0; k < G->arcnum; ++k) {
		printf("输入顶点对:");
		const VerTexType v1 = getchar();
		const int i = Locate(v1, G);
		const VerTexType v2 = getchar();
		const int j = Locate(v2, G);
		getchar();	//吸收回车
	}
	printf("已建立\n");
}
int main() {
	AMGraph AG;
	CreateUDN(&AG);
	return 0;
}
