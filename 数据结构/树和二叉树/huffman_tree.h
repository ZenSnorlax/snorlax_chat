#include<stdio.h>
#include<stdlib.h>
typedef struct huffmanTree{
int parent;
int lchild, rchild;
int weight;
} HTNode, *HuffmanTree;
void InitHuffmanTree(HuffmanTree *HT, int n){
	for (int i = 1; i < 2 * n; ++i){
		(*HT)[i].parent = 0;
		(*HT)[i].rchild = 0;
		(*HT)[i].rchild = 0;
		(*HT)[i].weight = 0;
	}
	for(int i = 1; i <= n; ++i)
		scanf("%d", &(*HT)[i].weight);
}
void Select(HuffmanTree *HT, int *s1, int len){
	int i;
	for( i = 1; i <= len; ++i)
		if(!(*HT)[i].parent)
	break;
	*s1 = i;
	while(i <= len){
		if((*HT)[i].parent)
		continue;
		if((*HT)[i].weight < (*HT)[*s1].weight)
		*s1 = i;
	}
}
void CreateHuffmanTree(HuffmanTree *HT, int n){
	if(n <= 1)
	return;
	int m = 2 * n -1;
	(*HT) = (HTNode *)malloc(sizeof(HTNode) * (m + 1));
	InitHuffmanTree(HT, n);
	for (int i = n + 1; i <= m; ++i){
		int rchild, lchild;
		Select(HT, &lchild, i - 1);
		(*HT)[i].lchild = lchild;
		(*HT)[lchild].parent = i;
		Select(HT, &rchild, i -1);
		(*HT)[i].rchild = rchild;
		(*HT)[rchild].parent = i;
		(*HT)[i].weight = (*HT)[rchild].weight + (*HT)[lchild].weight;
	}

}
int main(int argc,  char *argv[]){

}
