/*
 * translate.h
 *
 *  Created on: 2013-4-26
 *      Author: y
 */

#ifndef TRANSLATE_H_
#define TRANSLATE_H_

#include "stack.h"

void M_init();

void test(item *);
void null_f(item *);

void M_func_content_declare(item *);

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


void smt_if(item *);
void smt_while(item *);
//void smt_(item *);
//void (item *);
//void (item *);

/*
void (item *);

*/

#endif /* TRANSLATE_H_ */
