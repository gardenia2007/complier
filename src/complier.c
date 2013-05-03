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

void init(){
	lineno = 1;
	temp_addr = 80000;
	offset = 10000;
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
		printf("%d:\t%s", k+1, code.data[k]);
	}

	return EXIT_SUCCESS;
}
