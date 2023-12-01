#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXNUM 101
typedef struct HTNode{
    int weight;
    int parent, rchild, lchild;
}HTNode;
void Select(const HTNode *HT, const int end, int *index){
    int min= MAXNUM;
    for(int i=1;i<=end;++i){
        if(HT[i].parent)
            continue;
        if(min>HT[i].weight){
            min=HT[i].weight;
            *index=i;
        }
    }
}
void CreateHuffmanTree( HTNode **PHT, int n){
    if(n<=1)
        return;
    int m = 2 * n - 1;
    (*PHT) = (HTNode *)malloc((m + 1) * sizeof(HTNode));
    HTNode *HT = (*PHT);
    for(int i = 1; i<=m; ++i){
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    for(int i = 1; i<= n; ++i)
        scanf("%d", &HT[i].weight);
    printf("初始化结束\n");
    for(int i = n + 1; i<= m; ++i){
        int lchild;
        Select(HT, i - 1, &lchild);
        HT[i].lchild = lchild;
        HT[lchild].parent = i;
        int rchild;
        Select(HT, i - 1, &rchild);
        HT[i].rchild = rchild;
        HT[rchild].parent = i;
    }
}

void CreateHuffmanCode(const HTNode* HT, const int n, char* **PHC){
    (*PHC) = (char**)malloc((n + 1) * sizeof(char*));
    char **HC = (*PHC);
    char* cd = (char*)malloc(sizeof(char) * n);
    cd[n-1] = '\0';
    //free(cd);
    for(int i =  1; i <= n; ++i){
        int start = n - 1;
        int c = i;
        int f = HT[i].parent;
        while(f){
            --start;
            if(HT[f].lchild == c)
                cd[start] = '0';
            else
                cd[start] = '1';
            c = f;
            f = HT[f].parent;
        }
        HC[i] = (char*)malloc((n - start) * sizeof(char));
        strcpy(HC[i], &cd[start]);

    }
   free(cd);
}
void HuffmanCode_Print(char **HC) {
    for(int i = 1; i < 10; ++i)
        puts(HC[i]);
}

int main(){
    HTNode *HT = NULL;
    char **HC = NULL;
    CreateHuffmanTree(&HT, 10);
    CreateHuffmanCode(HT, 10, &HC);
    HuffmanCode_Print(HC);
}