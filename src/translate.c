/*
 * tanslate.c
 *
 *  Created on: 2013-4-26
 *      Author: y
 */

#include "global.h"
#include "translate.h"

void exp_var_exp_item(item *it){
	printf("%d = %d\n", symtable[s->d[s->t-2].attr.value].offset, s->d[s->t].attr.value);
}
void var_id(item *it){
	it->attr.value = s->d[s->t].attr.value;
}

void mulop_mul(item *i){
	i->attr.value = MUL;
}
void mulop_div(item *i){
	i->attr.value = DIV;
}
void addop_plus(item *i){
	i->attr.value = PLUS;
}

void addop_minus(item *i){
	i->attr.value = MINUS;
}
//
//void addop_(item *i){
//	i->attr.value = DIV;
//}

void term_factor(item *it){
	it->attr.value = s->d[s->t].attr.value;
	it->attr.value_type = s->d[s->t].attr.value_type;;
}
void exp_item_term(item *it){
	it->attr.value = s->d[s->t].attr.value;
	it->attr.value_type = s->d[s->t].attr.value_type;;
}
void addop_mulop(item *it){
	it->attr.value = new_temp();

	switch(s->d[s->t - 1].attr.value){
	case PLUS:
		printf("%d = %d + %d\n", it->attr.value, s->d[s->t - 2].attr.value, s->d[s->t].attr.value);
		break;
	case MINUS:
		printf("%d = %d - %d\n", it->attr.value, s->d[s->t - 2].attr.value, s->d[s->t].attr.value);
		break;
	case MUL:
		printf("%d = %d * %d\n", it->attr.value, s->d[s->t - 2].attr.value, s->d[s->t].attr.value);
		break;
	case DIV:
		printf("%d = %d / %d\n", it->attr.value, s->d[s->t - 2].attr.value, s->d[s->t].attr.value);
		break;
	default:break;
	}
}
void exp_item_addop(item *it){
	addop_mulop(it);
}
void term_term_mulop_factor(item *it){
	addop_mulop(it);
}
void factor_exp_item(item *it){
	it->attr.value = s->d[s->t - 1].attr.value;
	it->attr.value_type = VALUE_ADDR;
}
void factor_id(item *it){
	it->attr.value = symtable[s->d[s->t].attr.value].offset;
	it->attr.value_type = VALUE_ADDR;
}
void factor_num(item *it){
	it->attr.value = s->d[s->t].attr.value;
	it->attr.value_type = VALUE_IMM;
}

void M_func_content_declare(item * it){
}


void type_int(item * it){
	it->attr.type = INT;
	it->attr.width = 4;
}
void type_char(item * it){
	it->attr.type = CHAR;
	it->attr.width = 1;
}
/*
s->d[s->t].attr.
*/
void t_type_type(item * it){
	it->attr.type = s->d[s->t].attr.type;
	it->attr.width = s->d[s->t].attr.width;
}
void declare_id(item * it){
	s->d[s->t].attr.offset = offset;
	update_offset(it->attr.value, offset); // 更新偏移地址
//	printf("it.val:%d, addr:%d\n", it->attr.value, offset);
	offset += s->d[s->t - 1].attr.width;
}

void M_init(){
//	offset = 0;
}

void test(item * item){
	printf("hello, state is %d\n", item->state);
}

// 无操作的空函数
void null_f(item * item){
	//printf("hello, state is %d\n", item->state);

	return;
}


