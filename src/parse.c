/*
 * parse.c
 *
 *  Created on: 2013-3-15
 *      Author: y
 */

#include "global.h"
#include "production.h"

#undef STACK_DATA_TYPE
#define STACK_DATA_TYPE int

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
	int state, tmp_state, cur_lex, act;

	cur_lex = lexan();
	push(0, stack);

	while(1){
		state = get_top(stack);
		act = action[state][cur_lex];
		if(act == E){
			error_handle(lineno, "Parse error\n");
			break;
		}else if(act < 0){ // shift
			push(-act, stack);
			cur_lex = lexan();
			lex = cur_lex;
		}else if(act > 0){ // reduce
			pop_num(production[act].right_count, stack);
			tmp_state = get_top(stack);
			push(go_to[tmp_state][production[act].left], stack);
			printf("%d\t: %s => %s\n", act, production_left[production[act].left], production[act].right);
		}else if(act == 0){ // accept
			printf("accept\n");
			break;
		}else{
			error_handle(lineno, "Parse error\n");
		}
	}
}
