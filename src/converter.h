/*
 * converter.h
 *	Description: Header for converter.
 */

#ifndef CONVERTER_H
#define CONVERTER_H

#define base32(a) (a) < 10 ? (a) + '0' : (a - 10) + 'A'
#define OUTPUT_BASE 32
#define WORD_SIZE_IN_BASE (int) ((WORD_SIZE + (int) log2(OUTPUT_BASE) - 1) / (int) log2(OUTPUT_BASE))
char* base10to32enc(long unsigned int value);

#endif
