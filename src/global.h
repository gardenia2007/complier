/*
 * global.h
 *
 *  Created on: 2013-3-15
 *      Author: y
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"

#define EOS		'\0'
#define DONE	-1
#define ERROR	-2
#define NONE	-1
#define STR_MAX	999
#define SYM_MAX	100


struct symentry{
	char * lexptr;
	int token;
};


FILE* fp;

char token[128];
int tokenval;
struct symentry symtable[SYM_MAX];

int lex;
int lineno;



void init_symbol();
int look_up(char *);
int insert(char *, int);

void parse();
int lexan();
void error_handle(int, char *);


#endif /* GLOBAL_H_ */
