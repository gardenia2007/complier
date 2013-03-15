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
#include "word.h"

#define EOS		'\0'
#define DONE	-1

FILE* fp;

char token[128];

int lineno;

void init_symbol();
void parse();
int lexan();
void error_handle(int, char *);


#endif /* GLOBAL_H_ */
