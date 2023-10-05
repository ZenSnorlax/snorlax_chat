#include<stdio.h>
typedef struct Node{
    int val;
    struct Node* next;
}ListNode;
ListNode* List_Creat_H(){
    ListNode L;
    L.next=NULL;L.val=1;
    ListNode* node=&L;
    while(node->val!=0){
      node=(ListNode*)malloc(sizeof(ListNode));
      scanf("%d",node->val);
      node->next=L.next;
      L.next=node;      
    }
  return  L.next;
}
void List_Insert(ListNode* l,int i,int x){ 
  ListNode L;L.next=l;L.val=1;
  ListNode* p=&L;
  while(--i&&p->next) p=p->next;
  ListNode* q=(ListNode*)malloc(sizeof(ListNode));
  q->val=x;
  q->next=p->next;
  p->next=q;
}
void List_Delete(ListNode* l,int i){
  ListNode L;L.next=l;L.val=1;
  ListNode* p=&l;
  while(--i&&p->next) p=p->next;
  ListNode* q=p->next;
  p->next=q->next;
  free(q);
}
void List_Find(ListNode* l,int i){
  ListNode* L;L->next=l;L->val=1;
  ListNode* p=&L;
  while(--i&&p) p=p->next; 
  if(!p) printf("no find\n");
  else printf("%d\n",p->val);
}
void List_Print(ListNode* l)
{
    ListNode* p=l;
    while(p){
        printf("%d ",p->val);
        p=p->next;
    }
    printf("\n");
}

int main(){
  ListNode* l1=List_Creat_H();
  int i,x;
  List_Print(l1);
  scanf("%d",&i);
  List_Insert(l1,i,x);
  List_Delete(l1,i);
  List_Print(l1);
  List_Find(l1,i);
  return 0;
}