/*
 * tanslate.c
 *
 *  Created on: 2013-4-26
 *      Author: y
 */

#include "global.h"
#include "translate.h"

void test(item * item){
	printf("hello, state is %d\n", item->state);
}

// 无操作的空函数
void null_f(item * item){
	//printf("hello, state is %d\n", item->state);

	return;
}


