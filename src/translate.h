/*
 * translate.h
 *
 *  Created on: 2013-4-26
 *      Author: y
 */

#ifndef TRANSLATE_H_
#define TRANSLATE_H_

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
//void (item *);
//void (item *);
//void (item *);

/*
void (item *);

*/

#endif /* TRANSLATE_H_ */
