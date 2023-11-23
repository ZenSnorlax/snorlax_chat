#include <stdio.h>
#include <stdlib.h>
typedef struct huffman
{
  int weight;
  int parent, lchild, rchild;
} HTNode, *HuffmanTree;
// 构造哈夫曼树
void CreateHuffmanTree(HuffmanTree *HT, int n);
int main(int argc, char *argv[])
{

}
void CreateHuffmanTree(HuffmanTree *HT, int n)
{
  // 初始化
  if (n <= 1)
    return;
  int m = 2 * n - 1;
  *HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
  for (int i = 1; i <= m; ++i)
  {
    (*HT)[i].parent = 0;
    (*HT)[i].lchild = 0;
    (*HT)[i].rchild = 0;
  }
  for (int i = 1; i <= n; ++i)
    scanf("%d", &(*HT)[i].weight);
  // 创建哈夫曼树
  for (int i = n + 1; i <= m; ++i)
  {
    // 通过n-1次的选择、删除、合并来创建哈夫曼树
    int s1, s2;
    //select(*HT, i - 1, s1, s2);
    (*HT)[s1].parent = i;
    (*HT)[s2].parent = i;
    (*HT)[i].lchild = s1;
    (*HT)[i].rchild = s2;
    (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
  }
}
void CreateHuffmancode(HuffmanTree *HT, HuffmanTree){


}

