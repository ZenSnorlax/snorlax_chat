#include<stdio.h>
typedef struct node{
    int val;
    struct node* next;
}ListNode;
//lA无头节点，lB,lC有头节点,lB->next为指向首元节点的指针
void List_Divid(ListNode* lA,ListNode* lB,ListNode* lC){
    ListNode L;L.next=lA;L.val=1;
    ListNode *p=lB,*q=lC;
    p->next=NULL;p->val=1;
    q->next=NULL;q->val=1;
    while(!L.next){
        if(L.next->val>0){
            ListNode *temp=L.next;
            L.next=L.next->next;
            temp->next=p->next;
            p->next=temp;
        }
        else if(L.next->val<0){
            ListNode *temp=L.next;
            L.next=L.next->next;
            temp->next=q->next;
            q->next=temp;
        }
    }
}
int main(){

}