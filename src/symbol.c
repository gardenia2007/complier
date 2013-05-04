/*
 * symbol.c
 *
 *  Created on: 2013-3-15
 *      Author: y
 */

#include "symbol.h"

char lexemes[STR_MAX];
int lastchar = 0;
int lastentry = 0;

symentry keywords[] = {
		{"if",		IF,		KEYWORD},
		{"else",	ELSE,	KEYWORD},
		{"while",	WHILE,	KEYWORD},

		{"void",	VOID,	KEYWORD},
		{"int",		INT,	KEYWORD},
		{"bool",	BOOL,	KEYWORD},
		{"float",	FLOAT,	KEYWORD},
		{"char",	CHAR,	KEYWORD},
		{"string",	STRING,	KEYWORD},

		{"break",	BREAK,	KEYWORD},
		{"continue",CONTINUE,KEYWORD},

		{"main",	MAIN,	KEYWORD},
		{"return",	RETURN,	KEYWORD},

		{"true",	B_TRUE,	KEYWORD},
		{"false",	B_FALSE,KEYWORD},

		{"and",		AND,	KEYWORD},
		{"or",		OR,		KEYWORD},
		{"not",		NOT,	KEYWORD},

		{"print_int",NULL,	FUNCTION},

		{0,		0}
};

void init_symbol() {
	symentry * p;
	for(p = keywords; p->token; p++)
		insert(p->name, p->token);
}

int look_up(char * s){
	int p;
	for(p = lastentry; p > 0; p--)
		if(strcmp(s, symtable[p].name) == 0)
			return p;
	return 0;
}

int insert(char * s, int token){
	int len = 0;
	len = strlen(s);
	if(len + lastchar + 1 >= STR_MAX)
		error_handle(lineno, "lexemes full");
	if(lastentry + 1 >= SYM_MAX)
		error_handle(lineno, "symbol table full");
	lastentry += 1;
	symtable[lastentry].token = token;
	symtable[lastentry].name = &lexemes[lastchar];
	strcpy(&lexemes[lastchar], s);
	lastchar += ( len + 1 );
	return lastentry;
}

void update_offset(int p, int offset){
	symtable[p].offset = offset;
}

/*
int insert_str(){
}
*/



