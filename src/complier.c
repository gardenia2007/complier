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
#include "translate.h"
//#include "symbol.h"
#include <stdlib.h>

char header[] = { ""
		".section .data\n"
		"\t\n"
		".section .bss\n"
		"\t.comm temp, 1024\n"
		".section .text\n"
		".globl _start\n"
		"_start:\n"
		"\tnop\n"
		"\tpushl %ebp\n"
		"\tmovl %esp, %ebp\n" // 临时
//		"movl $4321, %eax\n"
//		"call print_int\n"
		"\n"
		"" };

char footer[] = { ""
		"\n"
		"\tmovl $0, %ebx\n"
		"\tmovl $1, %eax\n"
		"\tint $0x80\n"
		"\n" };

char lib_echo[] = { ""
		"movl $4, %eax\n"
		"movl $1, %ebx\n"
		"" };

void init() {
	lineno = 1;
	temp_addr = 0;
	offset = 0;
	code.quad = 0;
	cur_func = -1;

	init_symbol();
}

int main(void) {
	int k;
	FILE *asm_fp;
	fp = fopen("/home/y/workspace/complier/test", "r");
	asm_fp = fopen("/home/y/workspace/complier/asm/out.s", "w");
	if (fp == NULL) {
		printf("FATAL ERROR: SOURCE FILE OPEN FAILED!\n");
		return -1;
	}
	if (asm_fp == NULL) {
		printf("FATAL ERROR: OUTPUT FILE CAN'T WRITE!\n");
		return -1;
	}

	init();
	lalr_parse();

	printf("%s", header);
	fprintf(asm_fp, "%s", header);
	for (k = 0; k < code.quad; k++) {
		if (code.label[k] == LABEL) { // 输出label
			printf("L_%d:\n", k + 1);
			fprintf(asm_fp, "L_%d:\n", k + 1);
		}
		printf("\t%s", code.data[k]);
		fprintf(asm_fp, "\t%s", code.data[k]);
	}

	printf("%s", footer);
	fprintf(asm_fp, "%s", footer);

	return EXIT_SUCCESS;
}
