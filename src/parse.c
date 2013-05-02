/*
 * parse.c
 *
 *  Created on: 2013-3-15
 *      Author: y
 */

#include "global.h"
#include "production.h"


#include "stack.h"

void parse() {
	//lex = lexan();
	//STACK * stack = init_stack();
	while ((lex = lexan()) != DONE) {
		if(lex != ERROR)
		//printf("<\t%d,\t%d\t>\n", lex, tokenval);
		//push(lex, stack);
		lex = lexan();
	}
}

void lalr_parse(){
	STACK * stack = init_stack();
	int cur_lex, act;
	//item *it = (item *)malloc(sizeof(item));
	item it, tmp;
	it.state = 0;
	cur_lex = lexan();
	push(it, stack);

	while(1){
		tmp = get_top(0, stack);
		act = action[tmp.state][cur_lex];
		if(act == E || tmp.state == E){
			error_handle(lineno, "Parse error\n");
			break;
		}else if(act < 0){ // shift
			it.state = -act;
			push(it, stack);
			cur_lex = lexan();
			lex = cur_lex;
		}else if(act > 0){ // reduce & translate
			// 用第‘act’个产生式归约

			(*production[act].f)(&it); // 调用翻译函数

			pop_num(production[act].right_count, stack);

			tmp = get_top(0, stack); // 弹栈后获取栈顶元素
			//stack->data[stack->top].state;
			it.state = go_to[tmp.state][production[act].left];
			push(it, stack);

			printf("%d\t: %s => %s\n", act, production_left[production[act].left], production[act].right);
		}else if(act == AC){ // accept
			printf("accept\n");
			break;
		}else{
			error_handle(lineno, "Parse error");
		}
	}
}
