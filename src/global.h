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

#define STACK_DATA_TYPE	item

/* 符号表项 */
typedef struct{
	char * lexptr;
	int token;
	int addr;
}symentry;

typedef struct{
	int lex;
	int val;
}lex_s;

// 符号的属性
typedef struct{
	int offset;
	int width;

	int type;
	int value;

	int true_list;
	int false_list;
} attribute ;

// 栈中的一项
typedef struct{
	int state;
	attribute attr;
}item;

FILE* fp;

char token[128];
int tokenval;
symentry symtable[SYM_MAX];

int lex; // 当前token
int lineno; // 当前行号

// 全局栈
STACK * stack;

// 符号表全局偏移
int offset;


void init_symbol();
int look_up(char *);
int insert(char *, int);

void lalr_parse();
void parse();
int lexan();
void error_handle(int, char *);


#endif /* GLOBAL_H_ */
