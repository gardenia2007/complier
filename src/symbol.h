/*
 * symbol.h
 *
 *  Created on: 2013-5-4
 *      Author: y
 */

#ifndef SYMBOL_H_
#define SYMBOL_H_

#include "global.h"

#define VARIABLE	0
#define FUNCTION	1
#define KEYWORD		2

#define MAGIC_NUM	(VAR_MAX + 444)

// 存放id的name字符串
char id_names[STR_MAX];

/* 变量符号表项 */
typedef struct{
	char *name; // 指向id_names
	int type;
	int offset; // 偏移 相对于%ebp或temp
}variable_item;

/* 函数符号表项 */
typedef struct{
	char *name; // 指向id_names


	int last_v;
	int v_offset;
	variable_item v[VAR_MAX]; // 最多VAR_MAX个变量

	int last_p;
	int p_offset;
	variable_item p[VAR_MAX]; // 最多VAR_MAX个参数

	int ret_type;
}func_item;


func_item s_t[FUNC_MAX]; // symbol_table

// 当前处理（翻译）到的的函数在符号表中的下标
int cur_func;

// 关键字
typedef struct{
	char * name;
	int lex;
}keyword;


void init_symbol();
int look_up(char *, int ); // 查找变量（局部变量和参数）
int look_up_func(char *);
int insert(char *, int, int);
void update_offset(int p, int offset, int);


#endif /* SYMBOL_H_ */
