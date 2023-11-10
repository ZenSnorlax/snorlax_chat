#include<stdio.h>
typedef struct TreeNode{
	ElemType date;// 结点数据域
	struct TreeNode *r, *l;
}TreeNode;
//先序遍历
void traversing_tree_mlr(TreeNode *root){
	if(!root) return;
	printf("%d \n", root->date);
	traversing_tree_mlr(root->l);
	traversing_tree_mlr(root->r);
}
//中序遍历
void traversing_tree_lmr(TreeNode *root){
	if(!root) return;
	traversingtree_lmr(root->l);
	printf("%d \n", root->date);
	traversing_tree_lmr(root->r);
}
//后序遍历
void traversing_tree_lrm(TreeNode *root){
	if(!root) return;
	traversing_tree_lrm(root->l);
	traversing_tree_lrm(root->r);
	printf("%d \n", root->date);
}
//先序构造二叉树
void create_tree_mlr(TreeNode *root){
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
		create_tree_mlr(root->l);
		root->r = (TreeNode *)malloc(sizeof(TreeNode));
		if (!root->r) exit(1);
		create_tree_mlr(root->r);
	}
}
//中序构造二叉树
void create_tree_lmr(TreeNode *root){
	char ch;
	scanf("%c", &ch);
	if (ch == '#') {
		free(root);
		root = NULL;
	}
	else {	
		root->l = (TreeNode *)malloc(sizeof(TreeNode));
		if (!root->l) exit(1);
		create_tree_lmr(root->l);
		root->date = ch;
		root->r = (TreeNode *)malloc(sizeof(TreeNode));
		if (!root->r) exit(1);
		create_tree_lmr(root->r);
	}
}
//后序构造二叉树
void create_tree_lrm(TreeNode *root){
	char ch;
	scanf("%c", &ch);
	if (ch == '#') {
		free(root);
		root = NULL;
	}
	else {	
		root->l = (TreeNode *)malloc(sizeof(TreeNode));
		if (!root->l) exit(1);
		create_tree_lrm(root->l);
		root->r = (TreeNode *)malloc(sizeof(TreeNode));
		if(!root->r) exit(1);
	    create_tree_lrm(root->r);
		root->date = ch;
             }
}
