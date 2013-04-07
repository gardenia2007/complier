/*
 * parse.c
 *
 *  Created on: 2013-3-15
 *      Author: y
 */

#include "global.h"

#undef STACK_DATA_TYPE
#define STACK_DATA_TYPE char

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
}

void lalr_parse(){
	STACK * stack = init_stack();
	int state, cur_lex, act;
	int action[128][128]= {{0}};
	push(0, stack);

	while(1){
		state = get_top(stack);
		act = action[state][cur_lex];
		if(act < 0){ // shift

		}else if(act > 0){ // reduce

		}else if(act == 0){ // accept
			printf("accept\n");
		}else{
			error_handle(lineno, "Parse error\n");
		}
	}
}
