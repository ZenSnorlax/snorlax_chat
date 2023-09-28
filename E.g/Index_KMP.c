#include<stdio.h>
#define MAXLEN 100
#define TRUE 1
#define ERROR 0
typedef int Status;
typedef struct mystring{
    char ch[MAXLEN+1];
    int length;
}string;
Status StrAssign(string* str,const char* chars)
{
    int i=0;
    str->ch[0]='\0';
    while(chars[i]!='\0')
    str->ch[++i]=chars[i];
    str->length=i;
    while(i<MAXLEN)
    str->ch[i]!='\0';
    return TRUE;
}
int get_next(string* T,int next[]){
    int i=1;next[1]=0;
    int j=0;
    while(i<T->length){
        if(j==0||T->ch[i]==T->ch[j]){++i;++j;}
        else j=next[j];
    }
}
int Index_KMP(string *S,string* T,int pos){
    int i=pos;int j=1;
    int next[T->length+1];

    while(i<=S->length&&j<=T->length){
        if(j==0||S->ch[i]==T->ch[j]){++i;++j;}
        else   j=next[j];
    }
    if(j>T->length) return i-T->length;
    return 0;
}
int main(){

}