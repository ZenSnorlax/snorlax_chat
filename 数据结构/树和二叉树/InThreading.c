#include <stdio.h>
#include <stdlib.h>
// 二叉树定义
typedef struct treenode
{
    char date;
    struct treenode *l, *r;
    char LTag, RTag;
} TreeNode;
// pre指向上一节点
TreeNode *pre;
void InCreateTree(TreeNode *);
void InTreading(TreeNode *);
void InitTreeNode(TreeNode **);
int main(int argc, char *argv[])
{
    TreeNode *threading_tree;
    InitTreeNode(&threading_tree);
    InitTreeNode(&pre);
}
// 初始化节点
void InitTreeNode(TreeNode **p)
{

    TreeNode *ptr = *p;
    ptr = (TreeNode *)malloc(sizeof(TreeNode));
    ptr->LTag = '0';
    ptr->RTag = '0';
    ptr->l = NULL;
    ptr->r = NULL;
}
// 中序构造二叉树
void InCreateTree(TreeNode *root)
{
    char ch = getchar();
    if (ch == '#')
    {
        free(root);
        root = NULL;
    }
    else
    {
        root->l = (TreeNode *)malloc(sizeof(TreeNode));
        InCreateTree(root->l);
        root->date = ch;
        root->r = (TreeNode *)malloc(sizeof(TreeNode));
        InCreateTree(root->r);
    }
}
// 中序线索化
void InTreading(TreeNode *root)
{
    if (root == NULL)
        return;
    InTreading(root->l);
    if (root->l == NULL)
    {
        root->l = pre;
        root->LTag = '1';
    }
    if (pre->r == NULL)
    {
        pre->r = root;
        pre->RTag = '1';
        pre = root;
    }
    InTreading(root->r);
}
