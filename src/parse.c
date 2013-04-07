/*
 * parse.c
 *
 *  Created on: 2013-3-15
 *      Author: y
 */

#include "global.h"

void parse() {
	//lex = lexan();
	while ((lex = lexan()) != DONE) {
		if(lex != ERROR)
		printf("<\t%d,\t%d\t>\n", lex, tokenval);
		//lex = lexan();
	}
}
