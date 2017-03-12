/*
 * errorHandler.h
 *
 *  Created on: Jan 31, 2016
 *      Author: Gur Telem
 */

#ifndef ERROR_H
#define ERROR_H

/* Funny constants comes here. */
#define WOW_IMPRES "Wow, that must be frustrating ;)"
#define TEASING "Did you even try to avoid errors?"
#define MAYBE_RANDOM "Are you sure this program is not just random generated text?"
#define ONLY_FIX "Just fix that and you're done. "
#define CLEAN_CODE "Your code is clean. I'm impressed. "
#define LITTLE_BUGS "99 little bugs in the code\n99 little bugs in the code\nTake one down, patch it around.\n 127 LITTLE BUGS IN THE CODE!"

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"

/* Statuses */
#define	EXIT_FAILURE	1	/* Failing exit status.  */
#define	EXIT_SUCCESS	0	/* Successful exit status.  */

/* Constants */
#define ERROR_MAX_LEN 200

/* Error messages */
#define ERR_STR "File:%s Line:%d: %s\n"
#define TOO_LESS_FILES "Not enough arguments. You need to specify at least one file to compile.\n"
#define ASSEMBLER_ERR "Assembler error! Could not finish for file: %s%s.\n"
#define ASSEMBLER_SUCCESS "Assembler finished for file: %s%s.\n"
#define TOO_LESS_ARGS "Not enough arguments. "
#define MULTI_LABEL_DEF "Multiple definitions of label %s. Please define each label exactly once. "
#define LABEL_NAME_ERR "Unknown error with label name. Received value of NULL. "
#define OUT_OF_RAM "Insufficient memory. "
#define OUT_OF_STORAGE "Insufficient storage space. "
#define LINE_EXCEEDS_LEN "The input line exceeds the max length. "
#define ILLEGAL_LABEL "Illegal label name: %s. "
#define SYNTAX_ERROR "Syntax error. "
#define MISSING_OP "No operator or instruction is recognised. "
#define UNKNOWN_OP "The operator's or instruction's name is not recognised. "
#define UNKNOWN_LABEL "Unknown label: %s. "
#define INVALID_ARG "Invalid argument: %s. "
#define UNKNOWN_ARG_TYPE "The argument type could not be resolved. "
#define EMPTY_ARG "An argument cannot be empty. "
#define WRONG_STR_FORMAT "The argument is in a wrong string format. "
#define WRONG_ARG_COUNT "Wrong amount of arguments. "
#define UNKNOWN_ERR "An unknown error has been encountered. "
#define CANNOT_GET_RND "No symbols to get a random address from. "
#define WRONG_ARG_FOR_FUNC "Incompatible arguments' type for function. "
#define ENT_TO_UNDEF "Call to .entry with undefined label: %s. "

/* Global variables */
extern char errMsg[];

extern char *currFileName;
FLAG error(int status);
void report(int lineIndex);

#endif


