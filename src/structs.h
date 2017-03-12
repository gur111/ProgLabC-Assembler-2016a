/*
 * structs.h
 *
 *  Created on: Jan 18, 2016
 *      Author: Gur
 */


#ifndef STRUCTS_H
#define STRUCTS_H

/* Structure of an operation (command) word */
typedef struct {
	unsigned int decode 	: DECODE_SIZE;
	unsigned int destOperand: OPERAND_SIZE;
	unsigned int srcOperand : OPERAND_SIZE;
	unsigned int opcode 	: OPCODE_SIZE;
	unsigned int group 		: GROUP_SIZE;
	unsigned int rnd 		: RND_SIZE;
	unsigned int zeroBit	: UNUSED_SIZE;
} cmd_word;

/* Structure of an argument word */
typedef struct {
	unsigned int decode: DECODE_SIZE;
	unsigned int value : VALUE_SIZE;
} arg_word;


typedef struct {
	unsigned int decode 	: DECODE_SIZE;
	unsigned int destOperand: RED_OPERAND_SIZE;
	unsigned int srcOperand : RED_OPERAND_SIZE;
	unsigned int zeroBit 	: UNUSED_SIZE;
} reg_word;

typedef union {
	cmd_word cmd;
	reg_word reg;
	arg_word num;
	unsigned int print :15;
} word;

typedef struct{
	char *label;
	int cmd;
	char **args;
	bool isEffectless;
	bool isEOF;
}input_line;

#endif
