#include<stdio.h>
typedef struct node{
    int val;
    struct node *next;
}ListNode;
//返回指向首元节点的指针
ListNode* reverse(ListNode *l){
    ListNode L;L.next=l;L.val=1;
    ListNode L1;L1.next=NULL;L1.val=1;
    while(!L.next){
        ListNode *temp=L.next;
        L.next=L.next->next;
        temp->next=L1.next;
        L1.next=temp;
    }
    return L1.next;
}
int main(){

}