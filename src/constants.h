/*
 * constants.h
 *
 *  Created on: Jan 18, 2016
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

/* Size constants */
#define MAX_MEMORY_SIZE 1000
#define MAX_FILE_ZISE 1000
#define MEMORY_START 100
#define LINE_MAX_LEN 81 /* Extra one for \0 */
#define MAX_ARG_COUNT ((LINE_MAX_LEN - 3)/2 + 1) /* Max arg count assuming shortest command is 3 letters and shortest args are at least 1 character */
#define DECODE_SIZE 2
#define OPERAND_SIZE 2
#define RED_OPERAND_SIZE 6
#define OPCODE_SIZE 4
#define GROUP_SIZE 2
#define RND_SIZE 2
#define UNUSED_SIZE 1
#define VALUE_SIZE 13
#define OPCODES_AMOUNT 16
#define WORD_SIZE 15
#define REG_AMOUNT 8
#define EXT_LEN 4 /* Length of the extension file name. */
#define INPUT_EXT ".as"
#define OBJ_EXT ".ob"
#define EXT_EXT ".ext"
#define ENT_EXT ".ent"

/*
 *	The three types of encode:
 *	absolute, external and relocatable.
 */
enum ENCODE {
	ABS = 0, EXT, RLC
};
/*
 * The four types of addressing:
 * immediate, direct, random and direct-register.
 */
typedef enum ADDRESSING {
	IMD = 0, DIR, RND, REG
} addressing;
/* Arguments amount enums */
enum NUM_OF_ARGS {
	NO_ARGS = 0, ONE_ARG, TWO_ARGS
};

/* Registers enum table */
typedef enum {
	R0, R1, R2, R3, R4, R5, R6, R7
} reg;

/* Opcodes enum table */
typedef enum {
	MOV,
	CMP,
	ADD,
	SUB,
	NOT,
	CLR,
	LEA,
	INC,
	DEC,
	JMP,
	BNE,
	RED,
	PRN,
	JSR,
	RTS,
	STOP
} OPCODE; /* !Retain the current order! see info in inst_type */

typedef enum {
	EMPTY, COMMENT, INSTUCTION, ACTION
} sentence_type;
typedef enum {
	DOT_DATA = OPCODES_AMOUNT, DOT_STRING, DOT_EXTERN, DOT_ENTRY
} inst_type; /* The order this enum and the OPCODE must stay identical to the order of the "ops" array in the getLine function so the index will match the enums values*/

/* String constants */
#define NEWLINE '\n'
#define COMMENT_SIGN ';'
#define LABEL_DELIM ':'
#define STR_DELIM '"'
#define REG_FLAG 'r'
#define IMD_FLAG '#'
#define RND_FLAG '*'
#define ARG_SEPERATOR ','
#define SPACE ' '

/* Flag status */
typedef enum {
	ASM_SUCCESS, ASM_FAILURE
} FLAG;

typedef enum {
	false = 0, true = 1
} bool;

#endif
