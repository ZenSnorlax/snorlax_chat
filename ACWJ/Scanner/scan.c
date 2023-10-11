#include"defs.h"
#include"data.h"
#include"decl.h"
//Lexical scanning
//Copyright (c) 2019 Warren Toomey,GPL3

//Return the position of character c
//in string s,or -1 if c not found
static int chrpos(char *s,int c){
    char *p;
    p=strchar(s,c);
    return (p? p-s:-1);
}
//Get the character from the input file
static int next(void){
    int c;

    if(Putback){
        c=Putback;
        Putback=0;
        return c;
    }
    c=fgetc(Infile);
    if('\n'==c) Line++;
    return c;
}
//Put back an unwanted character
static void putback(int c){
    Putback=c;
}
//Skip past input that we don't need to deal with
//i.e whiitespace,newLines,Return the first
//character we do need to deal with
static int skip(void){
    int c;
    c=next();
    while(' '==c||'\t'==c||)
    c=next();
    return c;
}
static int scanint(int c){
    int k,val=0;
    while((k=chrops("0123456789",c))>=0){
        val=val*10+k;
        c=next();
    }
    putback(c);
    return val;
}
int scan(struct token *t){
    int c;
    c=skip();
    switch(c){
        case EOF:
        return 0;
        case '+':
        t->token=T_PLUS;
        break;
        case '-':
        t->token=T_MINUS;
        break;
        case '*':
        t->token=T_STAR;
        break;
        case '/':
        t->token=T_SLASH;
        break;
        default:
        if(isdigit(c)){
            t->intvalue=scanint(c);
            t->token=T_INTLIT;
            break;
        }
        printf("Ub=nrecognised character %c on line %d\n",c,line);
        exit(1);
    }
    return 1;
}
