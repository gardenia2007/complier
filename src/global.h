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
#include "stack.h"

typedef int bool;

#define TRUE	1
#define FALSE	0


#define EOS		'\0'
#define DONE	0
#define ERROR	-2
#define NONE	-1
#define STR_MAX	999
#define SYM_MAX	100

#define VALUE_ADDR	1
#define VALUE_IMM	2


/* 符号表项 */
typedef struct{
	char * lexptr;
	int token;
	int offset;
}symentry;

typedef struct{
	int lex;
	int val;
}lex_s;

FILE* fp;

char token[128];
int tokenval;
symentry symtable[SYM_MAX];

int lex; // 当前token
int lineno; // 当前行号


// 符号表全局偏移
int offset;

// 全局栈
STACK * s;

// 全局临时变量地址分配
int temp_addr;
// 分配临时变量
int new_temp();

void init_symbol();
int look_up(char *);
int insert(char *, int);
void update_offset(int p, int offset);

void lalr_parse();
void parse();
int lexan();
void error_handle(int, char *);


#endif /* GLOBAL_H_ */
