/*
 * tanslate.c
 *
 *  Created on: 2013-4-26
 *      Author: y
 */
#include "translate.h"

void d_array_list_list(item *it) {
	int k = s->d[s->t - 2].attr.value;
	it->attr.value = k;
	array_init[k].data[array_init[k].i++] = s->d[s->t].attr.value;
	s_t[cur_func].v[s_t[cur_func].last_v].array_size++;
}
void d_array_list_item(item *it) {
	int k = get_free_array_init();
	it->attr.value = k;
	array_init[k].data[array_init[k].i++] = s->d[s->t].attr.value;
	s_t[cur_func].v[s_t[cur_func].last_v].array_size = 0;

}
void d_array_item_num(item *it) {
	it->attr.value = s->d[s->t].attr.value;
	it->attr.value_type = NUM;
}
void d_array_item_ch(item *it) {
	it->attr.value = s->d[s->t - 1].attr.value;
	it->attr.value_type = CHAR;
}
void declare_d_array(item *it) {

}
void d_array(item *it) {
	variable_item *t = &s_t[cur_func].v[s_t[cur_func].last_v];
	t->type = s->d[s->t - 4].attr.value;
	t->name = &id_names[s->d[s->t - 3].attr.value];
	t->offset = s_t[cur_func].v_offset; // 栈中分配
	t->array = ARRAY;
	t->array_init = NO_INIT;

	s_t[cur_func].v_offset -= (s->d[s->t - 1].attr.value
			* s->d[s->t - 4].attr.width); // update offset
	s_t[cur_func].last_v++;
}

// 复制到栈中实现数组的初始化
void d_array_init(item *it) {
	variable_item *t = &s_t[cur_func].v[s_t[cur_func].last_v];
	t->type = s->d[s->t - 8].attr.value;
	t->name = &id_names[s->d[s->t - 7].attr.value];
	t->offset = s_t[cur_func].v_offset; // 栈中分配
	t->array = ARRAY;
	// 初始值存放的数组
	t->array_init = s->d[s->t - 1].attr.value;

	s_t[cur_func].v_offset -= (s->d[s->t - 5].attr.value
			* s->d[s->t - 8].attr.width); // update offset
	s_t[cur_func].last_v++;
}
// 回填函数声明时不能确定的值
void func_backpatch(int m) {
	int i, k, addr, offset, temp;
//	char * buffer = code.data[s->d[s->t - 5].attr.offset];
	char * buffer = (char *) malloc(256);
	code.more[s->d[s->t - m].attr.offset] = buffer;
	func_item *t = &s_t[cur_func];
	// 回填局部變量所佔空間
	sprintf(code.data[s->d[s->t - m].attr.value],
			code.data[s->d[s->t - m].attr.value], -(t->v_offset + 4));

	// 数组初始化回填
	offset = 0;
	for (i = 0; i < t->last_v; i++) {
		if (t->v[i].array == ARRAY && t->v[i].array_init != NO_INIT) {
			addr = t->v[i].offset;
			for (k = 0; k < array_init[t->v[i].array_init].i; k++) {
				temp = sprintf(buffer + offset, "\tmovl $%d, %d(%%ebp)\n",
						array_init[t->v[i].array_init].data[k], addr);
				addr -= 4;
				offset += temp;
			}
			free_array_init(t->p[i].array_init);
		}
	}
}

// 没有参数的函数调用 结束
void func(item *it) {
	func_backpatch(5);
	if(s_t[cur_func].has_ret == FALSE)
		ret_smt_void(it);

}
// 有参数的函数调用 结束
void func_param(item *it) {
	func_backpatch(6);
	if(s_t[cur_func].has_ret == FALSE)
		ret_smt_void(it);
}
// 函数定义开始
void M_func_start(item * it) {
	char main[] = "main";
	new_func_item(); // 在函数符号表中新创建一项
	// 拷贝名字
	//	strcpy(s_t[cur_func].name, id_names + s->d[s->t].attr.value);
	s_t[cur_func].name = id_names + s->d[s->t].attr.value;
	// TODO 保存返回值类型
	//
	if (strcmp(s_t[cur_func].name, main) == 0) // 如果是主函數
		sprintf(code.data[code.quad++], "_start:\n\tpushl %%ebp\n",
				s_t[cur_func].name);
	else
		sprintf(code.data[code.quad++], "FUNC_%s:\n\tpushl %%ebp\n",
				s_t[cur_func].name);

	sprintf(code.data[code.quad++], "movl %%esp, %%ebp\n");
	// 局部变量所占空间,等函数归约出来后回填
	it->attr.value = code.quad;
	sprintf(code.data[code.quad++], "subl $%%d, %%%%esp\n");
	// 数组初始化，函数归约时回填
	it->attr.offset = code.quad;
	sprintf(code.data[code.quad++], "#array init\n");
}
// 第一个参数
void param_list_item(item *it) {
	// 放入局部变量的符号表中
	variable_item *t = &s_t[cur_func].p[s_t[cur_func].last_p];
	t->type = s->d[s->t].attr.type;
	t->name = &id_names[s->d[s->t].attr.value];
	t->offset = s->d[s->t].attr.offset;

	s_t[cur_func].last_p++;
}
void param_list(item *it) {
	// 操作和param_list_item是一样的
	// 放入局部变量的符号表中
	variable_item *t = &s_t[cur_func].p[s_t[cur_func].last_p];
	t->type = s->d[s->t - 1].attr.type;
	t->name = &id_names[s->d[s->t - 1].attr.value];
	t->offset = s->d[s->t - 1].attr.offset;

	s_t[cur_func].last_p++;
}
void param_item_id(item *it) {
	it->attr.value = s->d[s->t].attr.value; // id名字在id_names的起始位置

	it->attr.type = s->d[s->t - 2].attr.type;
	it->attr.offset = s_t[cur_func].p_offset; // 参数用
	// !必须放在这里
	s_t[cur_func].p_offset += s->d[s->t - 2].attr.width; // update offset
}
void param_item_array(item *it) {
	// TODO
}
// 函数内部变量声明
void M_func_content_declare(item * it) {
//	M_func_start(it);
}

// 无参数调用
void call_func(item *it) {
	int func = look_up_func(&id_names[s->d[s->t - 2].attr.value]);
	if (func == NOT_FOUND) { // 符号表没有找到
		fatal_error = TRUE;
		error_handle("Fatal Error : function symbol not found!");
	}
	sprintf(code.data[code.quad++], "call FUNC_%s\n", s_t[func].name);
}
void call_func_param(item *it) {
	int i;
	int func = look_up_func(&id_names[s->d[s->t - 3].attr.value]);
	if (func == NOT_FOUND) { // 符号表没有找到
		fatal_error = TRUE;
		error_handle("Fatal Error : function symbol not found!");
	}
	if (param_queue.tail + 1 != s_t[func].last_p) {
		fatal_error = TRUE;
		error_handle("Fatal Error : mismatch function parameters!");
	}
	for (i = 0; i <= param_queue.tail; i++) {
		switch (param_queue.value_type[i]) {
		case VALUE_ADDR:
			sprintf(code.data[code.quad++], "pushl %d\n", param_queue.value[i]);
			break;
		case VALUE_TEMP_ADDR:
			sprintf(code.data[code.quad++], "movl $%d, %%edi\n",
					param_queue.value[i]);
			sprintf(code.data[code.quad++], "pushl temp(,%%edi,4)\n");
			break;
		case VALUE_STACK_ADDR:
			sprintf(code.data[code.quad++], "pushl %d(%%ebp)\n",
					param_queue.value[i]);
			break;
		case VALUE_IMM:
			sprintf(code.data[code.quad++], "pushl $%d\n",
					param_queue.value[i]);
			break;
		}
	}
	// 调用
	sprintf(code.data[code.quad++], "call FUNC_%s\n", s_t[func].name);
	// 清理栈上的参数
	sprintf(code.data[code.quad++], "addl $%d, %%esp\n",
			s_t[func].p_offset - 8);
}
// 调用时参数列表
void d_param_item_id(item *it) {
	factor_id(it);
}
void d_param_item_num(item *it) {
	it->attr.value = s->d[s->t].attr.value;
	it->attr.value_type = VALUE_IMM;
}
void d_param_item_array(item *it) {
}
void d_param_list(item *it) {
	param_queue.tail++; // 进队
	param_queue.value[param_queue.tail] = s->d[s->t - 1].attr.value;
	param_queue.value_type[param_queue.tail] = s->d[s->t - 1].attr.value_type;
}
// 第一个参数
void d_param_list_item(item *it) {
	param_queue.tail = 0; // 清空队列
	param_queue.value[0] = s->d[s->t].attr.value;
	param_queue.value_type[0] = s->d[s->t].attr.value_type;
}
void smt_if_while(item *it) {
	it->attr.next_list = s->d[s->t].attr.next_list;
}

void smt_list(item *it) {
	back_patch(s->d[s->t - 2].attr.next_list, s->d[s->t - 1].attr.quad);
	it->attr.next_list = s->d[s->t].attr.next_list;
}
void loop_list(item *it) {
	back_patch(s->d[s->t - 3].attr.next_list, s->d[s->t - 1].attr.quad);
	it->attr.next_list = s->d[s->t].attr.next_list;
}
void smt_list_smt(item *it) {
	it->attr.next_list = s->d[s->t].attr.next_list;
}
void M_if_smt(item *it) {
	it->attr.next_list = make_list(code.quad);
	sprintf(code.data[code.quad++], "jmp L_%%d\n");
}
void if_smt(item *it) {
	back_patch(s->d[s->t - 6].attr.true_list, s->d[s->t - 3].attr.quad);
	it->attr.next_list = merge(s->d[s->t - 6].attr.false_list,
			s->d[s->t - 2].attr.next_list);
}
void if_smt_else(item *it) {
	list_item * t;
	back_patch(s->d[s->t - 13].attr.true_list, s->d[s->t - 10].attr.quad);
	back_patch(s->d[s->t - 13].attr.false_list, s->d[s->t - 3].attr.quad);

	t = merge(s->d[s->t - 6].attr.next_list, s->d[s->t - 2].attr.next_list);
	it->attr.next_list = merge(s->d[s->t - 9].attr.next_list, t);
}
void while_smt(item *it) {
	back_patch(s->d[s->t - 6].attr.true_list, s->d[s->t - 3].attr.quad);
	back_patch(s->d[s->t - 2].attr.next_list, s->d[s->t - 7].attr.quad);
	it->attr.next_list = s->d[s->t - 6].attr.false_list;
	sprintf(code.data[code.quad++], "jmp L_%d\n", s->d[s->t - 7].attr.quad);
	code.label[s->d[s->t - 7].attr.quad - 1] = LABEL;
}

void relop_EQ(item *it) {
	it->attr.value = EQ;
}
void relop_NE(item *it) {
	it->attr.value = NE;
}
void relop_LE(item *it) {
	it->attr.value = LE;
}
void relop_GE(item *it) {
	it->attr.value = GE;
}
void relop_LT(item *it) {
	it->attr.value = LT;
}
void relop_GT(item *it) {
	it->attr.value = GT;
}
void M_quad_E(item *it) {
	it->attr.quad = code.quad + 1;
}
void M_bool_exp_E(item *it) {
	it->attr.quad = code.quad + 1;
}
void bool_exp_or(item *it) {
	back_patch(s->d[s->t - 3].attr.false_list, s->d[s->t - 1].attr.quad);
	it->attr.true_list = merge(s->d[s->t - 3].attr.true_list,
			s->d[s->t].attr.true_list);
	it->attr.false_list = s->d[s->t].attr.false_list;
}
void bool_exp_and(item *it) {
	back_patch(s->d[s->t - 3].attr.true_list, s->d[s->t - 1].attr.quad);
	it->attr.false_list = merge(s->d[s->t - 3].attr.false_list,
			s->d[s->t].attr.false_list);
	it->attr.true_list = s->d[s->t].attr.true_list;
}
void bool_exp_not(item *it) {
	it->attr.false_list = s->d[s->t].attr.true_list;
	it->attr.true_list = s->d[s->t].attr.false_list;
}
void bool_exp_bracket(item *it) { // 括号
	it->attr.false_list = s->d[s->t - 1].attr.false_list;
	it->attr.true_list = s->d[s->t - 1].attr.true_list;
}
void bool_exp_relop(item *it) {
	char relop[6][3] = { "g", "l", "ge", "le", "ne", "e" };
	attribute *op1, *op2;
	op1 = &s->d[s->t - 2].attr;
	op2 = &s->d[s->t].attr;

	switch (op1->value_type) {
	case VALUE_STACK_ADDR:
		sprintf(code.data[code.quad++], "movl %d(%%ebp), %%eax\n", op1->value);
		break;
	case VALUE_IMM:
		sprintf(code.data[code.quad++], "movl $%d, %%eax\n", op1->value);
		break;
	default:
		break;
	}

	// op2类型
	switch (op2->value_type) {
	case VALUE_STACK_ADDR:
		sprintf(code.data[code.quad++], "cmp %d(%%ebp), %%eax\n", op2->value);
		break;
	case VALUE_IMM:
		sprintf(code.data[code.quad++], "cmp $%d, %%eax\n", op2->value);
		break;
	default:
		break;
	}

	it->attr.true_list = make_list(code.quad);
	sprintf(code.data[code.quad++], "j%s L_%%d\n",
			relop[s->d[s->t - 1].attr.value - GT]);
	it->attr.false_list = make_list(code.quad);
	sprintf(code.data[code.quad++], "jmp L_%%d\n");
}
void bool_exp_true(item *it) {
	it->attr.true_list = make_list(code.quad);
	sprintf(code.data[code.quad++], "jmp L_%%d\n");
}
void bool_exp_false(item *it) {
	it->attr.false_list = make_list(code.quad);
	sprintf(code.data[code.quad++], "jmp L_%%d\n");
}
void bool_exp_item(item *it) {
	it->attr.false_list = s->d[s->t].attr.false_list;
	it->attr.true_list = s->d[s->t].attr.true_list;
}

void exp_var_exp_item(item *it) {
	char asm_stack[] = "#stack\n\tmovl %%eax, %d(%%ebp)\n";
	// 從臨時變量中把偏移去出來
	char asm_array[] = "#array\n\tmovl $%d, %%edi\n"
			"\tmovl temp(,%%edi, 4), %%ebx\n"
			"\tmovl %%eax, 0(%%ebx)\n";

	char * _asm;
	switch (s->d[s->t - 2].attr.value_type) {
	case VALUE_STACK_ADDR:
		_asm = asm_stack;
		break;
	case VALUE_ARRAY:
		_asm = asm_array;
		break;
	default:
		break;
	}

	switch (s->d[s->t].attr.value_type) {
	case VALUE_TEMP_ADDR:
		sprintf(code.data[code.quad++], "movl $%d, %%edi\n",
				s->d[s->t].attr.value);
		sprintf(code.data[code.quad++], "movl temp(,%%edi,4), %%eax\n");
		sprintf(code.data[code.quad++], _asm, s->d[s->t - 2].attr.value);
		break;
	case VALUE_STACK_ADDR:
		sprintf(code.data[code.quad++], "movl %d(%%ebp), %%eax\n",
				s->d[s->t].attr.value);
		sprintf(code.data[code.quad++], _asm, s->d[s->t - 2].attr.value);
		break;
	case VALUE_IMM:
		sprintf(code.data[code.quad++], "movl $%d, %%eax\n",
				s->d[s->t].attr.value);
		sprintf(code.data[code.quad++], _asm, s->d[s->t - 2].attr.value);
		break;
	case VALUE_NONE:
		// 已经经过inc指令优化，不需要临时变量
		break;
	default:
		break;
	}
}

void exp_var_call_func(item *it) {
	char asm_stack[] = "#stack\n\tmovl %%eax, %d(%%ebp)\n";
	// 從臨時變量中把偏移去出來
	char asm_array[] = "#array\n\tmovl $%d, %%edi\n"
			"\tmovl temp(,%%edi, 4), %%ebx\n"
			"\tmovl %%eax, 0(%%ebx)\n";

	char * _asm;
	switch (s->d[s->t - 2].attr.value_type) {
	case VALUE_STACK_ADDR:
		_asm = asm_stack;
		break;
	case VALUE_ARRAY:
		_asm = asm_array;
		break;
	default:
		break;
	}

	sprintf(code.data[code.quad++], _asm, s->d[s->t - 2].attr.value);

}
void var_id(item *it) {
	factor_id(it);
}
void var_array(item *it) {
	int o = array(it);
	if (o < 0) {
		return;
	} else if (o >= MAGIC_NUM) { // 局部变量
		it->attr.value = new_temp();
		// 将数组值存入临时变量
		sprintf(code.data[code.quad++], "movl $%d, %%edi\n", it->attr.value);
		sprintf(code.data[code.quad++], "movl %%eax, temp(,%%edi,4)\n");
		it->attr.value_type = VALUE_ARRAY;
	} else { // 参数
		// TODO
		it->attr.value = s_t[cur_func].p[o].offset + 4;
		it->attr.value_type = VALUE_ADDR;
	}
}

void mulop_mul(item *i) {
	i->attr.value = MUL;
}
void mulop_div(item *i) {
	i->attr.value = DIV;
}
void addop_plus(item *i) {
	i->attr.value = PLUS;
}

void addop_minus(item *i) {
	i->attr.value = MINUS;
}

void term_factor(item *it) {
	it->attr.value = s->d[s->t].attr.value;
	it->attr.value_type = s->d[s->t].attr.value_type;
}
void exp_item_term(item *it) {
	it->attr.value = s->d[s->t].attr.value;
	it->attr.value_type = s->d[s->t].attr.value_type;
}
void addop_mulop(item *it) {
	attribute *r, *op1, *op2, *op;
	r = &it->attr;
	op = &s->d[s->t - 1].attr;
	op1 = &s->d[s->t - 2].attr;
	op2 = &s->d[s->t].attr;

	// 检查是否是自增运算
	// 需要检查是否是 i = i + 1 这种类型的运算
	if (op->value == PLUS && s->d[s->t - 4].attr.value_type == VALUE_STACK_ADDR) {
		r->value_type = VALUE_NONE;
		if (op1->value_type == VALUE_STACK_ADDR && op2->value_type == VALUE_IMM
				&& op2->value == 1 && s->d[s->t - 4].attr.value == op1->value) {
			sprintf(code.data[code.quad++], "incl %d(%%ebp)\n", op1->value);
			return;
		}
		if (op2->value_type == VALUE_STACK_ADDR && op1->value_type == VALUE_IMM
				&& op1->value == 1 && s->d[s->t - 4].attr.value == op2->value) {
			sprintf(code.data[code.quad++], "incl %d(%%ebp)\n", op2->value);
			return;
		}
	}

	r->value = new_temp();
	r->value_type = VALUE_TEMP_ADDR;

	// op1类型
	switch (op1->value_type) {
	case VALUE_STACK_ADDR:
		// 假定所有變量都在棧上
		sprintf(code.data[code.quad++], "movl %d(%%ebp), %%eax\n", op1->value);
		break;
	case VALUE_IMM:
		sprintf(code.data[code.quad++], "movl $%d, %%eax\n", op1->value);
		break;
	default:
		break;
	}
	// op2类型
	switch (op2->value_type) {
	case VALUE_STACK_ADDR:
		sprintf(code.data[code.quad++], "movl %d(%%ebp), %%ebx\n", op2->value);
		break;
	case VALUE_IMM:
		sprintf(code.data[code.quad++], "movl $%d, %%ebx\n", op2->value);
		break;
	default:
		break;
	}
	switch (op->value) {
	case PLUS:
		sprintf(code.data[code.quad++], "addl %%ebx, %%eax\n");
		break;
	case MINUS:
		sprintf(code.data[code.quad++], "subl %%ebx, %%eax\n");
		break;
	case MUL:
		sprintf(code.data[code.quad++], "mull %%ebx\n");
		break;
	case DIV:
		sprintf(code.data[code.quad++], "divl %%ebx\n");
		break;
	default:
		break;
	}
	// 结果一定是临时变量
	sprintf(code.data[code.quad++], "movl $%d, %%edi\n", r->value);
	sprintf(code.data[code.quad++], "movl %%eax, temp(,%%edi,4)\n");

}
void exp_item_addop(item *it) {
	addop_mulop(it);
}
void term_term_mulop_factor(item *it) {
	addop_mulop(it);
}
void factor_exp_item(item *it) {
	it->attr.value = s->d[s->t - 1].attr.value;
	it->attr.value_type = s->d[s->t - 1].attr.value_type;
}
int array(item *it) {
	// 查符號表
	int o = look_up(&id_names[s->d[s->t - 3].attr.value], cur_func);
	if (o == NOT_FOUND) { // 符号表没有找到
		fatal_error = TRUE;
		error_handle("Fatal Error : variable symbol not found!");
		fatal_error = TRUE;
		return -1;
	}
	// 取下标
	int index = s->d[s->t - 1].attr.value;
	// 下标存在%eax中
	switch (s->d[s->t - 1].attr.value_type) {
	case VALUE_IMM:
		// 与数组大小取模，防止越界
		if (index == -1)
			index = s_t[cur_func].v[o - MAGIC_NUM].array_size;
//		index %= s_t[cur_func].v[o - MAGIC_NUM].array_size;
		sprintf(code.data[code.quad++], "movl $%d, %%eax\n", index);
		break;
	case VALUE_STACK_ADDR:
		sprintf(code.data[code.quad++], "movl %d(%%ebp), %%eax\n", index);
		break;
	case VALUE_TEMP_ADDR:
		// 临时变量的值应该还存放在%eax中
		//sprintf(code.data[code.quad++], "movl $%d, %eax", index);
		break;
	default:
		error_handle("unknown array index");
		break;
	}

	// 下标存在%eax中，计算后偏移在%eax中
	// 计算下标对应的偏移
	sprintf(code.data[code.quad++], "movl $4, %%ebx\n");
	sprintf(code.data[code.quad++], "mull %%ebx\n");
	sprintf(code.data[code.quad++], "negl %%eax\n");
	sprintf(code.data[code.quad++], "addl $%d, %%eax\n",
			s_t[cur_func].v[o - MAGIC_NUM].offset);
	sprintf(code.data[code.quad++], "addl %%ebp, %%eax\n");
	return o;
}
void factor_array(item *it) {
	int o = array(it);
	if (o < 0) {
		return;
	} else if (o >= MAGIC_NUM) { // 局部变量
		it->attr.value = new_temp();
		// 将数组值存入临时变量
		sprintf(code.data[code.quad++], "movl $%d, %%edi\n", it->attr.value);
		sprintf(code.data[code.quad++], "movl 0(%%eax), %%eax\n");
		sprintf(code.data[code.quad++], "movl %%eax, temp(,%%edi,4)\n");
		it->attr.value_type = VALUE_TEMP_ADDR;
	} else { // 参数
		// TODO
		it->attr.value = s_t[cur_func].p[o].offset + 4;
		it->attr.value_type = VALUE_ADDR;
	}
}
void factor_id(item *it) {
//	int offset = look_up(s->d[s->t].attr.value);
	int o = look_up(&id_names[s->d[s->t].attr.value], cur_func);
	if (o == NOT_FOUND) { // 符号表没有找到
		fatal_error = TRUE;
		error_handle("Fatal Error : variable symbol not found!");
	} else if (o >= MAGIC_NUM) { // 局部变量
		it->attr.value = s_t[cur_func].v[o - MAGIC_NUM].offset; // -8(%ebp)
	} else { // 参数
		it->attr.value = s_t[cur_func].p[o].offset;
	}
	it->attr.value_type = VALUE_STACK_ADDR;
}
void factor_num(item *it) {
	it->attr.value = s->d[s->t].attr.value;
	it->attr.value_type = VALUE_IMM;
}

void ret_smt_id(item *it) {
	int o = look_up(&id_names[s->d[s->t].attr.value], cur_func);
	if (o == NOT_FOUND) { // 符号表没有找到
		fatal_error = TRUE;
		error_handle("Fatal Error : variable symbol not found!");
	} else if (o >= MAGIC_NUM) { // 局部变量
		sprintf(code.data[code.quad++], "movl %d(%%ebp), %%eax\n",
				s_t[cur_func].v[o - MAGIC_NUM].offset);
	} else { // 参数
		sprintf(code.data[code.quad++], "movl %d(%%ebp), %%eax\n",
				s_t[cur_func].p[o].offset);
	}
	ret_smt_void(it);
}
void ret_smt_num(item *it) {
	sprintf(code.data[code.quad++], "movl $%d, %%eax\n",
			s->d[s->t].attr.value);
	ret_smt_void(it);
}
void ret_smt_void(item *it) {
	s_t[cur_func].has_ret = TRUE;
	sprintf(code.data[code.quad++], "addl $%d, %%esp\n",
			-(s_t[cur_func].v_offset + 4));
	sprintf(code.data[code.quad++], "popl %%ebp\n");
	sprintf(code.data[code.quad++], "ret\n");
}
void type_int(item * it) {
	it->attr.type = INT;
	it->attr.width = 4;
}
void type_char(item * it) {
	it->attr.type = CHAR;
	it->attr.width = 4;
}
void t_type_type(item * it) {
	it->attr.type = s->d[s->t].attr.type;
	it->attr.width = s->d[s->t].attr.width;
}
void declare_id(item * it) {

	variable_item *t = &s_t[cur_func].v[s_t[cur_func].last_v];
	t->type = s->d[s->t - 1].attr.type;
	t->name = &id_names[s->d[s->t].attr.value];
	t->offset = s_t[cur_func].v_offset; // 栈中分配的变量

	s_t[cur_func].v_offset -= s->d[s->t - 1].attr.width; // update offset
	s_t[cur_func].last_v++;
}

void M_init() {
//	offset = 0;
}

void test(item * item) {
	printf("hello, state is %d\n", item->state);
}

// 无操作的空函数
void null_f(item * item) {
	return;
}

