//约定 链表具有头节点
//函数传入头指针均指向头节点地址
#include<stdio.h>
#include<stdlib.h>
typedef struct node{
 int val;
 struct node next;
}ListNode;
//链表初始化
void List_Init(ListNode *p){
	p->next = NULL;
	p->val = 0;
}
//头插法
void Greate_List_H(ListNode *p,int n){

	printf("输入数据: ");
	for(int i = 0; i < n; i++){
		ListNode *node = (ListNode*)malloc(sizeof(ListNode));
		if(node == NULL)
			exit(1);
	 	scanf("%d", &node->val);
		node->next = p->next;
		p->next = node;
	}
	printf("建立成功!\n");
}
//尾插法
void Greate_List_R(ListNode *p,int n){
	ListNode *q = p;
	printf("输入数据: ");
	for(int i=0; i<n; i++){
		ListNode *node = (ListNode*)malloc(sizeof(ListNode));
		if(node == NULL)
			exit(1);
		scanf("%d", &node->val);
		node->next = NULL;
		q->next = node;
		q = q->next;
	}
	printf("建立成功!\n");
}

