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


int if_keyword(char * s){
	int p;
	for(p = 0; keywords[p] != 0; p++)
		if(strcmp(s, keywords[p].name) == 0)
			return keywords[p].lex;
	return ID;
}

int new_func_item() {
//	symentry * p;
	cur_func++;
	s_t[cur_func].space = 0;
	s_t[cur_func].last_item = -1;
	s_t[cur_func].ret_type = 0;
	s_t[cur_func].name = "\0";
}

int look_up(char * s, int func){
	int p;
	for(p = s_t[func].last_item; p >= 0; p--)
		if(strcmp(s,  s_t[func].v[p].name) == 0)
			return p;
	return -1; // 404 Not Found!
}

int insert(char * s, int lex, int func){
	func_item *f = &s_t[func];

	int len = 0;
	len = strlen(s);

	if(len + 1 > VAR_NAME_MAX)
		error_handle(lineno, "variable name too long!");
	if(f->last_item + 1 >= VAR_MAX)
		error_handle(lineno, "too many variables :(");
	f->last_item++;

	f->v[f->last_item].lex = lex;
	strcpy(f->v[f->last_item].name, s);

	return f->last_item; // 返回下标
}

void update_offset(int p, int offset, int func){
	s_t[func].v[p].offset = offset;
}

/*
int insert_str(){
}

int insert(char * s, int token){
	int len = 0;
	len = strlen(s);
	if(len + lastchar + 1 >= STR_MAX)
		error_handle(lineno, "lexemes full");
	if(lastentry + 1 >= VAR_MAX)
		error_handle(lineno, "symbol table full");
	lastentry += 1;
	symtable[lastentry].token = token;
	symtable[lastentry].name = &lexemes[lastchar];
	strcpy(&lexemes[lastchar], s);
	lastchar += ( len + 1 );
	return lastentry;
}
*/



