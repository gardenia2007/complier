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

typedef int bool;

#define TRUE	1
#define FALSE	0


#define EOS		'\0'
#define DONE	0
#define ERROR	-2
#define NONE	-1
#define STR_MAX	999
#define SYM_MAX	100

#define STACK_DATA_TYPE	int


typedef struct{
	char * lexptr;
	int token;
}symentry;

typedef struct{
	int lex;
	int val;
}lex_s;

FILE* fp;

char token[128];
int tokenval;
symentry symtable[SYM_MAX];

int lex;
int lineno;



void init_symbol();
int look_up(char *);
int insert(char *, int);

void lalr_parse();
void parse();
int lexan();
void error_handle(int, char *);


#endif /* GLOBAL_H_ */
