/*
 * translate.h
 *
 *  Created on: 2013-4-26
 *      Author: y
 */

#ifndef TRANSLATE_H_
#define TRANSLATE_H_
#include "global.h"
#include "stack.h"
#include "symbol.h"


// 全局临时变量地址分配
int temp_addr;
// 分配临时变量
int new_temp();

typedef struct{
	// 代码标号
	char label[MAX_ASM_LINE];
	// 生成的代码
	char data[MAX_ASM_LINE][MAX_CHAR_PER_ASM_LINE];
	// 当前生成的代码编号，即code数组下标
	int quad;
} s_code;
s_code code;
int next_quad();

list_item * make_list(int i);
list_item * merge(list_item *p, list_item *q);
void back_patch(list_item *p, int i);

// 翻译函数参数使用的队列
typedef struct{
	int tail;
	int value_type[32]; // IMM or ADDR
	int value[32]; // 最多支持32个参数
	// 暂时不考虑参数的类型，都默认为int
	int type[32]; // INT or CHAR or FLOAT
}s_param_queue;

s_param_queue param_queue;


void M_init();

void test(item *);
void null_f(item *);


void type_int(item *);
void type_char(item *);

void declare_id(item *);
void t_type_type(item *);

void factor_id(item *);
void factor_num(item *);
void factor_exp_item(item *);
void term_factor(item *);
void exp_item_term(item *);

void term_term_mulop_factor(item *);
void exp_item_addop(item *);

void mulop_mul(item *);
void mulop_div(item *);
void addop_plus(item *);
void addop_minus(item *);
void var_id(item *);
void exp_var_exp_item(item *);


void M_quad_E(item *);
void M_bool_exp_E(item *);
void bool_exp_or(item *);
void bool_exp_and(item *);
void bool_exp_not(item *);
void bool_exp_bracket(item *); // 括号
void bool_exp_relop(item *);
void bool_exp_true(item *);
void bool_exp_false(item *);
void bool_exp_item(item *);


void relop_EQ(item *);
void relop_NE(item *);
void relop_LE(item *);
void relop_GE(item *);
void relop_LT(item *);
void relop_GT(item *);

void M_if_smt(item *);
void if_smt(item *);
void if_smt_else(item *);
void while_smt(item *);
void smt_list(item *);
void smt_list_smt(item *);


void smt_if_while(item *);
void smt_while(item *);
//void smt_(item *);

// 函数参数调用
void d_param_list(item *);
void d_param_list_item(item *);
void d_param_item_id(item *);
void d_param_item_num(item *);
void d_param_item_array(item *);
void call_func(item *);
void call_func_param(item *);
//void (item *);


void M_func_start(item *);
void M_func_content_declare(item *);
void func(item *);
void func_param(item *);
// 函数参数声明
void param_list(item *);
void param_list_item(item *);
void param_item_id(item *);
void param_item_array(item *);
/*
void (item *);

*/

// 库函数
void lib_print(item *);

#endif /* TRANSLATE_H_ */
