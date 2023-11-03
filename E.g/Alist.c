#include<stdio.h>
#include<stdlib.h>
typedef struct node{
	int val;
	struct node *next;
}ListNode;
//头插法
ListNode* Greate_List_H(){
	ListNode head; head.val = 0;head.next = NULL;
	printf("输入数据: ");
	while(1){
		ListNode *node = (ListNode*)malloc(sizeof(ListNode));
		if(node == NULL)
			exit(1);
	 	scanf("%d", &node->val);
		if(node->val == 0) break;
		node->next = head.next;
		head.next = node;
	}	
	printf("建立成功!\n");
	return head.next;
}
ListNode* List_Insert(ListNode *p, int i, int x){
	ListNode *l = (ListNode*)malloc(sizeof(ListNode));
	if(l == NULL) exit(1);
	l->next = p; l->val = 0;
	while(l->next && --i)
	l = l->next;
	if(l->next == NULL) {printf("i 超出链表\n"); exit(1);}
	ListNode *node = (ListNode*)malloc(sizeof(ListNode));
	if(node == NULL) exit(1);
	node->val = x;
	node->next = l->next;
	l->next = node;
	return l->next;
}
ListNode* List_Delete(ListNode *p, int i){
	ListNode *l = (ListNode*)malloc(sizeof(ListNode));
	if(l == NULL) exit(1);
	l->next = p; l->val = 0;
	while(l->next && --i) l = l->next;
	if(l->next == NULL) {printf("i 超出链表\n"); exit(1);}
	ListNode *temp = l->next;
	l->next = temp->next;
	free(temp);
	return l->next;
}
void List_Find(ListNode* p, int i){
	int index = i;
	ListNode *l = p;
	while(l && --i)
		l->next = l;
	if(l == NULL) {printf("不存在\n"); exit(1);}
	printf("%d 对应的value: %d", index, l->val);


}

//输出链表
void List_Print(ListNode *p){
	ListNode *l = p;
	while(l){
		printf("%d ", l->val);
		l = l->next;
	}
	printf("\n");
}
int main(int argc, char *argv[]){
	ListNode *test = Greate_List_H();
	List_Print(test);
	test = List_Insert(test, 1, 1);
	List_Print(test);
	test = List_Delete(test, 1);
	List_Print(test);
	List_Find(test, 1);
	return 0;
}
