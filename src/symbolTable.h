/*
 * symbolTable.h
 *
 *  Created on: Mar 17, 2016
 *      Author: Gur Telem
 */

#ifndef SYMBOL_H
#define SYMBOL_H

typedef struct {
	char *labelName;
	int address;
	bool isExt;
	bool isOp;
} label;


bool addLabel(char *labelName, int address, bool isExt, bool isOp);
void printSymbolTable(void);/* This function is for debug only */
void freeSymbolTable(void);
label *getLabel(const char *name);
int getRandomAddress(void);
bool addExt(char *name, int address);
char *popExt(int *address);
bool addEnt(label *lbl);
char *popEnt(int *address);

#endif
