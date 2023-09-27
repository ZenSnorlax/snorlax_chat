#include<stdio.h>
#include<stdlib.h>
#define MAXLEN 100
#define TRUE 1
#define ERROR 0
#define OVERFLOW -1
typedef int Status;
typedef struct mystring{
    char ch[MAXLEN+1];
    int length;
}string;
Status StrAssign(string* str,const char* chars){
    int i=0;
    str->ch[0]='\0';
    for(i=0;chars[i]!='\0';++i)
        str->ch[i+1]=chars[i];
    str->length=i;
    while(i<MAXLEN)
        str->ch[i+1]='\0';
    return TRUE;
}
int Index_BP(string* S,string* T,int pos){
    int i=pos;
    int j=1;
    while(i<=S->length&&j<=T->length){
        if(S->ch[i]==T->ch[j]){++i;++j;}
        else{i=i-j+2;j=1;}
    }
    if(j>T->length) return i-T->length;
    else return 0;
}

