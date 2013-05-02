/*
 * stack.c
 *
 *  Created on: 2013-4-7
 *      Author: y
 */

#include "global.h"
#include "stack.h"


STACK * init_stack(){
	STACK * stack = (STACK *) malloc(sizeof(STACK));
	stack->t = -1;
	return stack;
}

bool push(STACK_DATA_TYPE val, STACK * s){
	s->t++;
	if(s->t == STACK_SIZE){
		printf("ERROR:\tStack is full!!\n");
		return FALSE;
	}
	s->d[s->t] = val;
	return TRUE;
}

void pop_num(int num, STACK * s){
	s->t-= num;
}

STACK_DATA_TYPE pop(STACK * s){
	STACK_DATA_TYPE tmp = get_top(0, s);
	s->t--;
	return tmp;
}

STACK_DATA_TYPE get_top(int offset, STACK * s){
	if(is_empty(s)){
		printf("ERROR:\tEmpty is empty!!\n");
		//return NULL;
	}
	return s->d[s->t + offset];
}

bool is_full(STACK * s){
	return s->t == STACK_SIZE ? TRUE : FALSE;
}

bool is_empty(STACK * s){
	return s->t == -1 ? TRUE : FALSE;
}
