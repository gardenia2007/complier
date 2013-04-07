/*
 * parse.c
 *
 *  Created on: 2013-3-15
 *      Author: y
 */

#include "global.h"
#include "stack.h"

void parse() {
	//lex = lexan();
	STACK * stack = init_stack();
	while ((lex = lexan()) != DONE) {
		if(lex != ERROR)
		//printf("<\t%d,\t%d\t>\n", lex, tokenval);
		push(lex, stack);
		//lex = lexan();
	}
	while(!is_empty(stack)){
		lex = pop(stack);
		printf("<\t%d\t>\n", lex);
	}
}

void lalr(int lex){

}
