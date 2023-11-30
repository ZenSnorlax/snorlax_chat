#include<stdio.h>
#include <stdlib.h>
#include <strings.h>
typedef struct HTNode{
	int weight;
	int parent, lchild, rchild;
}HTNode, *HuffmanTree;
void Select(HTNode *ht, int end, int *pd){
	int i;
	for( i=1;i<=end; ++i)
		if(ht[i].parent==0)
			break;
	int index=i;
	for(int k=i;k<=end;++k){
		if(!ht[k].parent)
			continue;
		if(ht[index].weight>ht[k].weight)
			index=k;
	}
	*pd=index;
}
void CreateHuffmanTree(HuffmanTree *HT, int n){
	if(n<=1)
		return;
	int m=2*n-1;
        (*HT)=(HTNode *)malloc((m+1)*sizeof(HTNode));
	HTNode *ht = (*HT);
	for(int i=1;i<=m;++i){
		ht[i].parent=0;
		ht[i].lchild=0;
		ht[i].rchild=0;
	}	
	for(int i=1;i<=n;++i)
		scanf("%d", &ht[i].weight);
	printf("初始化结束\n");
	for(int i=n+1; i<=m;++i){
		int lchild;		
		Select(ht, i-1, &lchild);
		ht[i].lchild=lchild;
		ht[lchild].parent=i;
		int rchild;
		Select(ht, i-1, &rchild);
		ht[i].rchild=rchild;
		ht[rchild].parent=i;
		ht[i].parent=ht[rchild].weight+ht[lchild].weight;
	}

}
