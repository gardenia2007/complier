/*
 * parse.c
 *
 *  Created on: 2013-3-15
 *      Author: y
 */

#include "global.h"
#include "production.h"


#include "stack.h"

void reset_it(item * it){
	//it->attr.value = 0;
	it->attr.value_type = VALUE_STACK_ADDR;
	it->attr.offset = 0;
	it->attr.type = 0;
	it->attr.addr = 0;
	it->attr.width = 0;
	it->attr.quad = code.quad + 1; // 回填翻译中标志非终结符的作用
	it->attr.true_list = NULL;
	it->attr.false_list = NULL;
	it->attr.next_list = NULL;
}

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
	int cur_lex, act;
	item it, tmp;

	s = init_stack();
	M_init();

	it.state = 0;
	cur_lex = lexan();
	push(it, s);

	while(1){
		reset_it(&it);
		tmp = get_top(0, s);
		act = action[tmp.state][cur_lex];
		if(act == E || tmp.state == E){
			error_handle(lineno, "Parse error\n");
			break;
		}else if(act < 0){ // shift
			it.state = -act;
			it.attr.value = tokenval; // 符号表项id等
			push(it, s);
			cur_lex = lexan();
			lex = cur_lex;
		}else if(act > 0){ // reduce & translate
			// 用第‘act’个产生式归约

			(*production[act].f)(&it); // 调用翻译函数

			pop_num(production[act].right_count, s);

			tmp = get_top(0, s); // 弹栈后获取栈顶元素
			//stack->data[stack->top].state;
			it.state = go_to[tmp.state][production[act].left];
			push(it, s);

//			printf("%d\t: %s => %s\n", act, production_left[production[act].left], production[act].right);
		}else if(act == AC){ // accept
			printf("Accept\n");
			break;
		}else{
			error_handle(lineno, "Parse error");
		}
	}
}
