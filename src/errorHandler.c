/*
 * errorHandler.c
 *
 *  Created on: Jan 31, 2016
 *      Author: Gur Telem
 */

#include "errorHandler.h"
#include "constants.h"

extern int flag;

char errMsg[ERROR_MAX_LEN];

/* Changes the status to error and returns the status */
FLAG error(int status) {
	flag = ASM_FAILURE;
	return ASM_FAILURE;
}

/* Prints an error message and exits the program */
void report(int lineIndex) {
	fprintf(stderr, ERR_STR, currFileName, lineIndex, errMsg);
}
