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
	stack->top = -1;
	return stack;
}

bool push(int val, STACK * s){
	s->top++;
	if(s->top == STACK_SIZE){
		printf("ERROR:\tStack is full!!\n");
		return FALSE;
	}
	s->data[s->top] = val;
	return TRUE;
}

elememt_type pop(STACK * s){
	if(is_empty(s)){
		printf("ERROR:\tEmpty is empty!!\n");
		return FALSE;
	}
	return s->data[s->top--];
}

bool is_full(STACK * s){
	return s->top == STACK_SIZE ? TRUE : FALSE;
}

bool is_empty(STACK * s){
	return s->top == -1 ? TRUE : FALSE;
}
