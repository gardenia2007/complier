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


/* 变量符号表项 */
typedef struct{
	char name[VAR_NAME_MAX];
	int lex;
	int offset; // 偏移
}variable_item;

/* 函数符号表项 */
typedef struct{
	char name[VAR_NAME_MAX]; // 函数名最长15个字符
	int space; // 所有变量所占的空间
	int last_item;
	int ret_type;
	variable_item v[VAR_MAX]; // 最多VAR_MAX个变量
}func_item;


func_item s_t[FUNC_MAX]; // symbol_table

// 当前所在的函数在符号表中的下标
int cur_func;

// 关键字
typedef struct{
	char * name;
	int lex;
}keyword;

keyword keywords[] = {
		{"if",		IF },
		{"else",	ELSE },
		{"while",	WHILE },

		{"void",	VOID },
		{"int",		INT },
		{"bool",	BOOL },
		{"float",	FLOAT },
		{"char",	CHAR },
		{"string",	STRING },

		{"break",	BREAK },
		{"continue",CONTINUE },

		{"main",	MAIN },
		{"return",	RETURN },

		{"true",	B_TRUE },
		{"false",	B_FALSE },

		{"and",		AND },
		{"or",		OR },
		{"not",		NOT },

		{0,		0}
};

#endif /* SYMBOL_H_ */
