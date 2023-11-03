//约定 主函数链表无头节点
//函数传入头指针均指向首元地址
#include<stdio.h>
#include<stdlib.h>
typedef struct node{
 int val;
 struct node *next;
}ListNode;
//头插法

ListNode* Greate_List_H(int n){
	ListNode head; head.val = 0;head.next = NULL;
	printf("输入数据: ");
	for(int i = 0; i < n; i++){
		ListNode *node = (ListNode*)malloc(sizeof(ListNode));
		if(node == NULL)
			exit(1);
	 	scanf("%d", &node->val);
		node->next = head.next;
		head.next = node;
	}
	printf("建立成功!\n");
	return head.next;
}
//尾插法
ListNode* Greate_List_R(int n){
	ListNode head; head.val = 0; head.next = NULL;
	ListNode *q = &head;
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
	return head.next;
}
//输出链表
void List_Print(ListNode *p){
	while(p){
		printf("%d ", p->val);
		p = p->next;
	}
	printf("\n");
}

