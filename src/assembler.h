#ifndef ASSEMBLER_H
#define ASSEMBLER_H

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include "errorHandler.h"

extern FLAG flag;
extern int ic;
extern int dc;

/* Main assembler */
FLAG assembler(FILE *sourceFile);
input_line *getLine(FILE *);
void freeLine(input_line *line);
bool validLabel(const char *);
bool validReg(const char* registerStr);
bool copyStr(char **dest, const char *src);
bool strToInt(const char *str, int *dest);

/* First run functions */
FLAG firstRun(FILE *sourceFile);
void relocate(int paddin);

/* Second run functions */
FLAG secondRun(FILE *);

#endif
