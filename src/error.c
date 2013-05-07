/*
 * error.c
 *
 *  Created on: 2013-3-15
 *      Author: y
 */

#include "global.h"

void error_handle(char * msg){
	printf("ERROR : %s in line %d\n", msg, lineno);
}
