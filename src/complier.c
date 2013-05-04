/*
 ============================================================================
 Name        : complier.c
 Author      : gardeniaxy@gmail.com
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "global.h"
#include <stdlib.h>

char header[] = {
		".section .data\n"
		".section .bss\n"
		"\t.comm temp, 1024"
		".section .text\n"
		".globl _start"
		"_start:\n"
		};

void init(){
	lineno = 1;
	temp_addr = 0;
	offset = 0;
	code.quad = 0;

	init_symbol();
}

int main(void) {
	int k;
	fp = fopen("/home/y/workspace/complier/test", "r");
	if (fp == NULL) {
		printf("FATAL ERROR: SOURCE FILE OPEN FAILED!\n");
		return -1;
	}
	init();
	lalr_parse();

	for(k = 0; k < code.quad; k++){
		if(code.label[k] == LABEL) // 输出label
			printf("LABEL_%d:\n", k + 1);
		printf("\t%s", code.data[k]);
	}

	return EXIT_SUCCESS;
}
