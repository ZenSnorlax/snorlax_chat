#include"common.h"
//约定传入指针指向首元节点地址
ListNode* increasing(ListNode* L1,ListNode* L2){
    ListNode head;
    ListNode* L= &head,*p = L1,*q = L2;
    L->val=0;L->next = NULL;
    while(p||q){
        ListNode* temp = NULL;
        if(p && (!q||p->val < q->val)){
            temp = p;
            p = p->next;
        }
        else if(q && (!p||q->val <= p->val)){
            temp = q;
            q = q->next;   
        }
        temp->next = L->next;
        L->next = temp;
    }
    return L->next;
}
int main(int argc, char *argv[]){
 ListNode *test1 = Greate_List_R(5);
 ListNode *test2 = Greate_List_R(5);
 ListNode *test3 = increasing(test1, test2);
 List_Print(test3);
 return 0;
}
