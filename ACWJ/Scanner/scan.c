#include"defs.h"
#include"data.h"
#include"decl.h"
//Lexical scanning
//Return the position of character c in string s,or -1 if c not found
static int chrops(char *s,int c){
	char *p;
	p=strchar(s,c);
	return (p?p-s:-1);
}
//Get the next character from the input file
static int next(void){
	int c;
	if(Putback){
		c=Putback;
		Putback=0;
		return c;
	}
	c=fgetc(Infile);
	if('\n'==c) len++;
	return c;
}
//Put back an unwanted character
static int skip(void){
	int c;
	while(' '==c||'\t'==c||'\r'==c||'\f'==c){
		c=next();
	}
	return c;
}
//Scan and return an integer Literal
//value from the input file.
//Store the value as a string int Text
static int scanint(int c){
	int k,val=0;
	//Convert each character into an int value
	while((k=chrpos("0123456789",c))>=0){
		val=val*10+k;
		c=next();
	}
	//we hit a non-integer charater,put in back
	putback(c);
	return val;
}
//scan and return the next token found int the input
//Return 1 if token valid,0 if no tokens left
int scan(struct token *t){
	int c;
	//Skip whitespace
	c=skip();
	//Determin the token based on
	//the input character
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
			//if it's adigit,scan the
			//Literal integer value in
			if(isdigit(c)){
				t->intvalue=scanint(c);
				t->token=T_INTLIT;
				break;
			}
			printf("Unrecognised character %c on line %d\n",c,Line);
			exit(1);
	}
	//We found a token
	return 1;
}
