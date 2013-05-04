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

/* 符号表项 */
typedef struct{
	char * name;
	int token; // 同lex
	int type; // VARIABLE or FUNCTION or KEYWORD
	int offset; // 偏移
}symentry;

symentry symtable[SYM_MAX];

#endif /* SYMBOL_H_ */
