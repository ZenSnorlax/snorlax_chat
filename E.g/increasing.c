#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
 int val;
 struct Node* next;
}ListNode;
//头插法
ListNode* increasing(ListNode* L1,ListNode* L2){
    ListNode head;
    ListNode* L=&head,*p=L1,*q=L2;
    L->val=0;L->next=NULL;
    while(p||q){
        ListNode* temp=NULL;
        if(!q||p->next<q->val){
            temp=p;
            p=p->next;
        }
        else if(!p||q->next<=p->next){
            temp=q;
            q=q->next;   
        }
        temp->next=L->next;
        L->next=temp;
    }
    return L->next;
}