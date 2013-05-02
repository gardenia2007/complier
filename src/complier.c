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
	init_symbol();
}

int main(void) {
	fp = fopen("/home/y/workspace/complier/test", "r");
	if (fp == NULL) {
		printf("FATAL ERROR: SOURCE FILE OPEN FAILED!\n");
		return -1;
	}
	init();
	lalr_parse();

	return EXIT_SUCCESS;
}
