/*
 * symbol.c
 *
 *  Created on: 2013-3-15
 *      Author: y
 */

#include "symbol.h"
int lastchar = 0;


keyword keywords[] = {
		{"if",		IF },
		{"else",	ELSE },
		{"while",	WHILE },

		{"void",	VOID },
		{"int",		INT },
		{"bool",	BOOL },
		{"float",	FLOAT },
		{"char",	CHAR },
		{"string",	STRING },

		{"break",	BREAK },
		{"continue",CONTINUE },

//		{"main",	MAIN },
		{"return",	RETURN },

		{"true",	B_TRUE },
		{"false",	B_FALSE },

		{"and",		AND },
		{"or",		OR },
		{"not",		NOT },

		{0,		0}
};

typedef struct{
	char name[VAR_NAME_MAX];
	int p_cnt; // 参数个数
	int p_space; // 参数所占空间
	int ret_type;
}lib_func_item;

lib_func_item lib_func[] = {
		{"print_int", 1, 4, INT},
		{"exit", 1, 4, VOID},
		{"print_br", 1, 4, VOID},
		{"", -1, -1, -1},
};

void insert_lib_func(){
	int i;
	for(i = 0; lib_func[i].ret_type != -1; i++){
		new_func_item();
		s_t[cur_func].name = lib_func[i].name;
		s_t[cur_func].last_p = lib_func[i].p_cnt;
		s_t[cur_func].p_offset = lib_func[i].p_space;
		s_t[cur_func].ret_type = lib_func[i].ret_type;
	}
}

void init_symbol(){
	insert_lib_func();
}

// 如果是关键字，返回其对应的lex，否则返回ID
int if_keyword(char * s){
	int p;
	for(p = 0; keywords[p].lex != 0; p++)
		if(strcmp(s, keywords[p].name) == 0)
			return keywords[p].lex;
	return ID;
}

int new_func_item() {
//	symentry * p;
	cur_func++;
	s_t[cur_func].last_v = 0;
	s_t[cur_func].v_offset = -4;
	s_t[cur_func].last_p = 0;
	s_t[cur_func].p_offset = 8;
	s_t[cur_func].ret_type = 0;
	s_t[cur_func].name = "\0";

}

int look_up_func(char * s){
	int i;
	for(i = cur_func; i >= 0; i--)
		if(strcmp(s,  s_t[i].name) == 0)
			return i;
	return -1; // 404 Not Found!
}
// 先从局部变量找，再找参数
int look_up(char * str, int func){
	int i;
	// 遍历局部变量表
	for(i = s_t[func].last_v - 1; i >= 0; i--)
		if(strcmp(str,  s_t[func].v[i].name) == 0)
			return i + MAGIC_NUM; // 区分局部变量和参数
	// 遍历参数表
	for(i = s_t[func].last_p - 1; i >= 0; i--)
		if(strcmp(str,  s_t[func].p[i].name) == 0)
			return i;
	return -1; // 404 Not Found!
}

int insert(char * s, int type, int func){
	func_item *f = &s_t[func];

	int len = 0;
	len = strlen(s);

	if(len + 1 > VAR_NAME_MAX)
		error_handle(lineno, "variable name too long!");
	if(f->last_v >= VAR_MAX)
		error_handle(lineno, "too many variables :(");
	f->last_v++;

	f->v[f->last_v].type = type;
	strcpy(f->v[f->last_v].name, s);

	return f->last_v; // 返回下标
}

void update_offset(int p, int offset, int func){
	s_t[func].v[p].offset = offset;
}
// 把id的名字存起来，返回其在一个字符串数组的起始位置
int insert_id_name(char * s){
	int len = 0, tmp;
	tmp = lastchar;
	len = strlen(s);
	if(len + lastchar + 1 >= STR_MAX)
		error_handle(lineno, "name array is full");
	strcpy(&id_names[lastchar], s);
	lastchar += ( len + 1 );
	return tmp;
}



