#include"common.h"
//返回指向首元节点的指针
ListNode* List_Reverse(ListNode *l){
    ListNode head; head.next = NULL; head.val = 0;
    ListNode *p = l;
    while(p){
	    ListNode *temp = p;
	    p = p->next;
	    temp->next = head.next;
	    head.next = temp;
    }
    return head.next;
}
int main(int argc, char* argv[]){
	ListNode *test = Greate_List_R(5);
	List_Print(test);
	ListNode *test1 = List_Reverse(test);
	List_Print(test1);
	return 0;
}
