/*
 * memory.c
 *
 *  Created on: 2013-5-2
 *      Author: y
 */
#include "translate.h"

// 生成新临时变量地址
int new_temp(){
	// TODO 临时变量分配
	temp_addr ++;
	return temp_addr;
}
// 在.bss段生成指定长度的数组
int new_array(){
	temp_addr += 4;
	return temp_addr;
}

// 下一行号
int next_quad(){
	//code.quad += 1;

	return code.quad;
}

// 造链表
list_item * make_list(int i){
	list_item * t = (list_item * )malloc(sizeof(list_item));
	t->quad = i;
	t->next = NULL;
	return t;
}

// 檢查是否已存在該項
bool exist_item(list_item *list, list_item *p){
	list_item * temp;
	for(temp = list; temp != NULL; temp = temp->next)
		if(temp == p) return TRUE;
	return FALSE;
}

// 合并两个链表
list_item * merge(list_item *p, list_item *q){
	list_item * temp, * p_tail;
	if( p == NULL)
		return q;

	// 找到p的尾部
	for(temp = p; temp != NULL; temp = temp->next)
		p_tail = temp;

	for(temp = q; temp != NULL; temp = temp->next){
		if(exist_item(p, temp)) // 如果前面的列表出現過該項，則跳過
			continue;
		else{ // 否則插入鏈表尾部
			p_tail->next = temp;
			p_tail = temp;
			p_tail->next = NULL;
		}
	}
	return p;
}

// 回填
void back_patch(list_item *p, int i){
	list_item * t;
	char * fmt;
	char buffer[MAX_CHAR_PER_ASM_LINE];
	for(t = p; t != NULL; t = t->next){
		fmt = code.data[t->quad];
		sprintf(buffer, fmt, i);
		strcpy(fmt, buffer);
		code.label[i-1] = LABEL;
		free(t); // 释放空间
	}
	p = NULL;
}

