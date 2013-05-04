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
//#include "stack.h"

typedef int bool;

#define TRUE	1
#define FALSE	0

//#define NULL	0
#define EOS		'\0'
#define DONE	0
#define ERROR	-2
#define NONE	-1
#define STR_MAX	999
#define SYM_MAX	100

#define VALUE_STACK_ADDR	1 // 栈上分配的变量
#define VALUE_IMM			2
#define VALUE_ADDR			3 // 内存中普通的变量
#define VALUE_TEMP_ADDR		4 // 临时变量.bss

#define NO_LABEL	0
#define LABEL		123

#define MAX_ASM_LINE	1024
#define MAX_CHAR_PER_ASM_LINE	64
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


// 全局临时变量地址分配
int temp_addr;
// 分配临时变量
int new_temp();

typedef struct{
	// 代码标号
	char label[MAX_ASM_LINE];
	// 生成的代码
	char data[MAX_ASM_LINE][MAX_CHAR_PER_ASM_LINE];
	// 当前生成的代码编号，即code数组下标
	int quad;
} s_code;
s_code code;
int next_quad();

// 回填使用的数据结构和函数
struct s_list_item{
	int quad;
	struct s_list_item * next;
};
typedef struct s_list_item list_item;
list_item * make_list(int i);
list_item * merge(list_item *p, list_item *q);
void back_patch(list_item *p, int i);

// 翻译函数参数使用的队列
typedef struct{
	int tail;
	int value_type[32]; // IMM or ADDR
	int value[32]; // 最多支持32个参数
	// 暂时不考虑参数的类型，都默认为int
	int type[32]; // INT or CHAR or FLOAT
}s_param_queue;

s_param_queue param_queue;

void init_symbol();
int look_up(char *);
int insert(char *, int);
void update_offset(int p, int offset);

void lalr_parse();
void parse();
int lexan();
void error_handle(int, char *);


#endif /* GLOBAL_H_ */
