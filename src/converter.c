/*
 * converer.c
 *	Description: Converts number from different bases.
 */

#include "assembler.h"    
#include "converter.h"
#include <math.h>

double log2(double);/* Throws an error without it for some reason */

char* base10to32enc(long unsigned int value) {
	char buffer[WORD_SIZE + 2];
	char *tmp;
	int offset = sizeof(buffer);
	buffer[--offset] = '\0';
	do {
		buffer[--offset] = base32(value % OUTPUT_BASE);
		if (offset <= 0)
			return NULL;
	} while (value /= OUTPUT_BASE);
	while (sizeof(buffer) / sizeof(buffer[0]) - offset <= WORD_SIZE_IN_BASE )/* Align to word size */
		buffer[--offset] = '0';
	copyStr(&tmp, buffer + offset);
	return tmp; /* warning: this must be freed by the user */
}
