#include"data.h"
#include"dacl.h"
#include"defs.h"
//Lexical scanning
//Skip past input that we don't need to deal with, i>e> whitespace,newLines.Return the first character
//we do need to deal with
static int skip(void){
    int c;
    c=next();
    while(' '=c||'\n'||'\r'==c||'\f'==c){
        c=next();
    }
    return c;
}
//Scan and return the next token found in the input
//Return 1 if token valid,0 if notokens left
int scan(struct token *t){
    int c;
    //Skip whitespace
    c=skip();
    //Determine the token based on the input character
    switch(c){
        case EOF:
        t->token=T_EOF;
        return 0;
        case '+':
        t->token=T_PLUS;
        break;
        case '-':
        t->token=T_NINUS;
        break;
        case '*':
        t->token=T_STAR;
        break;
        case '/':
        t->token=T_SLASH;
        break;
        default:
        //if it's a digit,scan the literal integer value in
        if(isdigit(c)){
            t->intvalue=scanint(c);
            t->token=T_INTLIT;
            break;
        }
        printf("Unrecognised character %c on line %d\n",c,line);
        exit(1);
    }
    //We found a token 
    return 1;
}