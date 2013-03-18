/*
 * parse.c
 *
 *  Created on: 2013-3-15
 *      Author: y
 */

#include "global.h"

void parse() {
	int lex;
	//lex = lexan();
	while ((lex = lexan()) != DONE) {
		printf("<%d,\t'%d'\t>\n", lex, tokenval);
		//lex = lexan();
	}
}
