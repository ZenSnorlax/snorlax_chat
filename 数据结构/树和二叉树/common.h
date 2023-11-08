#include<stdio.h>
typedef struct TreeNode{
	ElemType date;// 结点数据域
	struct TreeNode *r, *l;
}TreeNode;
//先序遍历
void TraversingTree_MLR(TreeNode *root){
	if(!root) return;
	printf("%d \n", root->date);
	TraversingTree_MLR(root->l);
	TraversingTree_MLR(root->r);
}
//中序遍历
void TraversingTree_LMR(TreeNode *root){
	if(!root) return;
	TraversingTree_LMR(root->l);
	printf("%d \n", root->date);
	TraversingTree_LMR(root->r);
}
//后序遍历
void TraversingTree_LRM(TreeNode *root){
	if(!root) return;
	Traversing_LRM(root->l);
	Traversing_LRM(root->r);
	printf("%d \n", root->date);
}
//先序构造二叉树
void CreateTree_MLR(TreeNode *root){
	char ch;
	scanf("%c", &ch);
	if (ch == '#') {
		free(root);
		root = NULL;
	}
	else {
		root->date = ch;
		root->l = (TreeNode *)malloc(sizeof(TreeNode));
		if (!root->l) exit(1);
		GreateTree_MLR(root->l);
		root->r = (TreeNode *)malloc(sizeof(TreeNode));
		if (!root->r) exit(1);
		GreateTree_MLR(root->r);
	}
}
//中序构造二叉树
void GreateTree_LMR(TreeNode *root){
	char ch;
	scanf("%c", &ch);
	if (ch == '#') {
		free(root);
		root = NULL;
	}
	else {	
		root->l = (TreeNode *)malloc(sizeof(TreeNode));
		if (!root->l) exit(1);
		GeateTree_LMR(root->l);
		root->date = ch;
		root->r = (TreeNode *)malloc(sizeof(TreeNode));
		if (!root->r) exit(1);
		GreateTree_LMR(root->r);
	}
}
//后序构造二叉树
void Greate_LRM(TreeNode *root){
	char ch;
	scanf("%c", &ch);
	if (ch == '#') {
		free(root);
		root = NULL;
	}
	else {	
		root->l = (TreeNode *)malloc(sizeof(TreeNode));
		if (!root->l) exit(1);
		GreateTree_LRM(root->l);
		root->r = (TreeNode *)malloc(sizeof(TreeNode));
		if(!root->r) exit(1);
		GreateTree_LRM(root->r);
		root->date = ch;
             }
}
