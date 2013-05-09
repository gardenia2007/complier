/* production.h
 *  Created on: 2013-4-8
 *      Author: y
 */



#ifndef PRODUCTION_H_
#define PRODUCTION_H_
#include "global.h"
#include "translate.h"
#include "stack.h"


#define PRODUCTION_LEFT_SIZE 32
#define PRODUCTION_RIGHT_SIZE 128




typedef struct{
	int left;
	char right[PRODUCTION_RIGHT_SIZE];
	int right_count;
	void (*f)(item *); // 翻译函数de指针
}PRODUCTION;


char * production_left[] = {
		"_start",
		"start",
		"main_func",
		"func",
		"func_content",
		"func_list",
		"ret_smt",
		"param_list",
		"param_item",
		"d_param_list",
		"d_param_item",
		"t_type",
		"ret_type",
		"type",
		"array",
		"d_array",
		"d_array_list",
		"d_array_item",
		"declare",
		"exp",
		"exp_item",
		"term",
		"factor",
		"addop",
		"mulop",
		"relop",
		"bolop",
		"ch",
		"smt_list",
		"smt",
		"call_func",
		"loop_list",
		"bool_exp",
		"bool_exp_item",
		"if_smt",
		"if_content",
		"var",
		"while_smt",
		"M_t_type",
		"M_func_content",
		"M_func_content_declare",
		"M_bool_exp",
		"M_quad",
		"M_if_smt",
		"declare_more_id"
};






PRODUCTION production[] = {
		{0,"_start->start",1,null_f},
		{0,"_start->start",1,null_f},
		{1,"start->func func_list",2,null_f},
		{1,"start->func",1,null_f},
		{2,"main_func->void main ( param_list ) { func_content } ",8,null_f},
		{9,"d_param_list->d_param_item d_param_list",2,d_param_list},
		{9,"d_param_list->d_param_item",1,d_param_list_item},
		{9,"d_param_list->, d_param_list",2,null_f},
		{10,"d_param_item->id [ ]",3,d_param_item_array},
		{10,"d_param_item->id",1,d_param_item_id},
		{10,"d_param_item->num",1,d_param_item_num},
		{7,"param_list->param_item param_list",2,param_list},
		{7,"param_list->param_item",1,param_list_item},
		{7,"param_list->, param_list",2,null_f},
		{8,"param_item->t_type M_t_type id [ ]",5,param_item_array},
		{8,"param_item->t_type M_t_type id",3,param_item_id},
		{38,"M_t_type->E",0,null_f},
		{18,"declare->declare semi t_type id",4,declare_id},
		{18,"declare->t_type declare_more_id",2,declare_id},
		{18,"declare->d_array",1,declare_d_array},
		{15,"d_array->t_type id = { d_array_list }",6,null_f},
		{16,"d_array_list->d_array_list,d_array_item",3,d_array_list_list},
		{16,"d_array_list->d_array_item",1,d_array_list_item},
		{17,"d_array_item->num",1,d_array_item_num},
		{17,"d_array_item->ch",1,d_array_item_ch},
		{11,"t_type->array",1,null_f},
		{11,"t_type->type",1,t_type_type},
		{13,"type->float",1,null_f},
		{13,"type->bool",1,null_f},
		{13,"type->char",1,type_char},
		{13,"type->int",1,type_int},
		{14,"array->type[num]",4,null_f},
		{3,"func->ret_type id M_func_start (){func_content}",8,func},
		{3,"func->ret_type id M_func_start (param_list){func_content}",9,func_param},
		{4,"func_content->M_func_content_declare declare semi smt_list semi",5,null_f},
		{4,"func_content->smt_listsemi",2,null_f},
		{39,"M_func_start->E",0,M_func_start},
		{40,"M_func_content_declare->E",0,M_func_content_declare},
		{12,"ret_type->type",1,null_f},
		{12,"ret_type->void",1,null_f},
		{6,"ret_smt->returnnum",2,null_f},
		{6,"ret_smt->returnid",2,null_f},
		{6,"ret_smt->return",1,null_f},
		{5,"func_list->func func_list",2,null_f},
		{5,"func_list->func",1,null_f},
		{23,"addop->+",1,addop_plus},
		{23,"addop->-",1,addop_minus},
		{24,"mulop->/",1,mulop_div},
		{24,"mulop->*",1,mulop_mul},
		{25,"relop->==",1,relop_EQ},
		{25,"relop-><>",1,relop_NE},
		{25,"relop-><=",1,relop_LE},
		{25,"relop->>=",1,relop_GE},
		{25,"relop-><",1,relop_LT},
		{25,"relop->>",1,relop_GT},
		{26,"bolop->and",1,null_f},
		{26,"bolop->or",1,null_f},
		{26,"bolop->not",1,null_f},
		{27,"ch->'char_set'",3,null_f},
		{30,"call_func->id()",3,call_func},
		{30,"call_func->id(d_param_list)",4,call_func_param},
		{19,"exp->var=exp_item",3,exp_var_exp_item},
		{19,"exp->var=call_func",3,null_f},
		{19,"exp->call_func",1,null_f},
		{36,"var->id[exp_item]",4,null_f},
		{36,"var->id",1,var_id},
		{20,"exp_item->exp_item addop term",3,exp_item_addop},
		{20,"exp_item->term",1,exp_item_term},
		{21,"term->term mulop factor",3,term_term_mulop_factor},
		{21,"term->factor",1,term_factor},
		{22,"factor->num",1,factor_num},
		{22,"factor->ch",1,null_f},
		{22,"factor->id",1,factor_id},
		{22,"factor->id[exp_item]",4,factor_array},
		{22,"factor->(exp_item)",3,factor_exp_item},
		{28,"smt_list->smt_list semi smt",3,smt_list},
		{28,"smt_list->smt",1,smt_list_smt},
		{42,"M_quad->E",0,M_quad_E},
		{29,"smt->exp",1,null_f},
		{29,"smt->ret_smt",1,null_f},
		{29,"smt->break",1,null_f},
		{29,"smt->continue",1,null_f},
		{29,"smt->while_smt",1,smt_if_while},
		{29,"smt->if_smt",1,smt_if_while},
		{31,"loop_list->loop_list semi M_quad smt",4,smt_list},
		{31,"loop_list->smt",1,smt_list_smt},
		{37,"while_smt->while(M_quad bool_exp){M_quad loop_list semi}",10,while_smt},
		{34,"if_smt->if(bool_exp) { M_quad loop_list semi}M_if_smt else { M_quad loop_list semi }",16,if_smt_else},
		{34,"if_smt->if ( bool_exp ) { M_quad loop_list semi }",9,if_smt},
		{43,"M_if_smt->E",0,M_if_smt},
		{32,"bool_exp->bool_exp_item and M_bool_exp bool_exp",4,bool_exp_and},
		{32,"bool_exp->bool_exp_item or M_bool_exp bool_exp",4,bool_exp_or},
		{32,"bool_exp->not bool_exp_item",2,bool_exp_not},
		{32,"bool_exp->bool_exp_item",1,bool_exp_item},
		{32,"bool_exp->(bool_exp)",3,bool_exp_bracket},
		{41,"M_bool_exp->E",0,M_bool_exp_E},
		{33,"bool_exp_item->exp_item relop exp_item",3,bool_exp_relop},
		{33,"bool_exp_item->true",1,bool_exp_true},
		{33,"bool_exp_item->false",1,bool_exp_false},
		{15,"d_array->t_type id [num]",5,d_array},
		{15,"d_array->t_type id [num]={d_array_list}",9,d_array_init},
		{18,"declare-> declare semi d_array",3, null_f},
		{0,"M_start->E",0,null_f},
		{44,"declare_more_id->id,declare_more_id",3,null_f},
		{44,"declare_more_id->id",1,null_f},

};


#endif /* PRODUCTION_H_ */
