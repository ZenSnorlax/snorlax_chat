#include"common.h"

ListNode* List_Init(ListNode *p){
	p->next = NULL;
	p->val = 0;
	return p;
}
//约定主函数链表无头节点
void List_Divid(ListNode *la, ListNode **plb, ListNode **plc){
	ListNode lb_head, lc_head;
	List_Init(&lb_head);
	List_Init(&lc_head);
	while(la){
		ListNode *temp = la;
		la = la->next;
		if(temp->val > 0){
			temp->next = lb_head.next;
			lb_head.next = temp;
		}
		else{
			temp->next = lc_head.next;
			lc_head.next = temp;
		}
	}
	*plb = lb_head.next;
	*plc = lc_head.next;
}
int main(int argc, char *argv[]){
ListNode *la = Greate_List_R(5);
ListNode *lb = NULL, *lc = NULL;
List_Divid(la, &lb, &lc);
List_Print(lb);
List_Print(lc);
return 0;
}
