/*
 * error.c
 *
 *  Created on: 2013-3-15
 *      Author: y
 */

#include "global.h"

void error_handle(int line, char * msg){
	printf("ERROR : %s in line %d\n", msg, line);
}
