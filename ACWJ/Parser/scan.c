#include"data.h"
#include"dacl.h"
#include"defs.h"
//Lexical scanning
//Skip past input that we don't need to deal with, i>e> whitespace,newLines.Return the first character
//we do need to deal with
static int skip(void){
  int c;
  c = next();
  while(' '=c||'\n'||'\r'==c||'\f'==c){
    c = next();
  }
  return c;
}
//Scan and return the next token found in the input
static int next(){
  int c;
  if (Putback) {
    c = Putback;
    Putback = 0;
    return c;
  }
  c = fgetc(Infile);
  if (c=='\0') {len++;
  }
return c;
}
//return position of string 
static int chrops(char *s, int c){
  char *p;
  p = strchr(s,c);
  return p?(p-s): -1;
}
//put 
static void putback(c){
  Putback = c;
}
//scan int
static int scanint(int c){
  int k, val = 0;
  while ((k = chrpos("0123456789",c)) >= 0) {
    val = val*10 + k;
    c = next();
  }
 putback(c); 
  return val;
}
//Return 1 if token valid,0 if notokens left
int scan(struct token *t){
    int c;
    //Skip whitespace
    c = skip();
    //Determine the token based on the input character
    switch(c){
        case EOF:
        t->token = T_EOF;
        return 0;
        case '+':
        t->token = T_PLUS;
        break;
        case '-':
        t->token = T_NINUS;
        break;
        case '*':
        t->token = T_STAR;
        break;
        case '/':
        t->token = T_SLASH;
        break;
        default:
        //if it's a digit,scan the literal integer value in
        if(isdigit(c)){
            t->intvalue = scanint(c);
            t->token = T_INTLIT;
            break;
        }
        printf("Unrecognised character %c on line %d\n",c,line);
        exit(1);
    }
    //We found a token 
    return 1;
}
