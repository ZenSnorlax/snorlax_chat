#include<stdio.h>
#include<stdlib.h>
typedef struct TreeNode{
	char data;
	struct TreeNode *lchild, *rchild;
}TreeNode, *Tree;
//先序建立二叉树
void CreateTree(TreeNode **proot){
	TreeNode *root=*proot;
	const char ch = getchar();
	if(ch == '#'){
		free(root);
		*proot=NULL;
	}
	else
	{
		root->data = ch;
		root->lchild = (TreeNode *)malloc(sizeof(TreeNode));
		CreateTree(&root->lchild);
		root->rchild = (TreeNode *)malloc(sizeof(TreeNode));
		CreateTree(&root->rchild);
	}	
}
//先序遍历
void PreOrderTraverse(TreeNode *root){
	if(!root) 
		return;
	putchar(root->data);
	PreOrderTraverse(root->lchild);
	PreOrderTraverse(root->rchild);
}
//中序遍历
void InOrderTraverse(TreeNode *root){
	if(!root)
		return;
	InOrderTraverse(root->lchild);
	putchar(root->data);
	InOrderTraverse(root->rchild);
}
//后序遍历
void PosOrderTraverse(TreeNode *root){
	if(!root)
		return;
	PosOrderTraverse(root->lchild);
	PreOrderTraverse(root->rchild);
	putchar(root->data);
}
int main(){

}
