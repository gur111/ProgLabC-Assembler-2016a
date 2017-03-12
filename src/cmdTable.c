#include <stdio.h>      /* NULL */
#include <stdlib.h>     /* malloc*/
#include "cmdTable.h"
#include "dataTable.h"
#include "converter.h"

/*############STATIC VARIABLES#############*/
cmdList cmd_list = { NULL, MEMORY_START };

/*############PRIVATE FUNCTIONS#############*/
/* Creates a cmd node with a dynamic allocated storage */
static cmdNode* createCmdNode(word row) {
	cmdNode* newCmdNode = NULL;
	if ((newCmdNode = malloc(sizeof(cmdNode)))) {
		newCmdNode->value = row;
		newCmdNode->next = NULL;
	}
	return newCmdNode;
}

/*############PUBLIC FUNCTIONS#############*/
/* increase the length of cmd_list by n */
void increaseCmdLength(int n) {
	cmd_list.length += n;
}

/* Gets the actual length of the cmd table */
int getCmdLength(void) {
	int cmdAmount = 0;
	cmdNode *cmd_node = cmd_list.head;
	while (cmd_node->next != NULL) { /* Get the length because the .length is not actually the length but the address by now */
		cmd_node = cmd_node->next;
		cmdAmount++;
	}
	return cmdAmount;
}

/* Adds argument word to cmd_list */
int addArg(word arg) {
	cmdNode *current, *newNode;
	if ((newNode = createCmdNode(arg))
			&& cmd_list.length + data_list.length < MAX_MEMORY_SIZE) {
		if (cmd_list.head == NULL)
			cmd_list.head = newNode;
		else {
			/* skip to the end of the list */
			for (current = cmd_list.head; current->next != NULL; current =
					current->next)
				;
			current->next = newNode;
		}
		cmd_list.length++;
		return true;
	}
	return false;
}

/* Adds command to cmd_list */
int addCmd(unsigned int decode, unsigned int destOperand,
		unsigned int srcOperand, unsigned int opcode, unsigned int group,
		unsigned int rnd) {
	cmdNode *current, *newNode;
	word newWord;

	newWord.cmd.decode = decode;
	newWord.cmd.destOperand = destOperand;
	newWord.cmd.srcOperand = srcOperand;
	newWord.cmd.opcode = opcode;
	newWord.cmd.group = group;
	newWord.cmd.rnd = rnd;
	newWord.cmd.zeroBit = 0;
	if ((newNode = createCmdNode(newWord))
			&& cmd_list.length + data_list.length < MAX_MEMORY_SIZE) {

		if (cmd_list.head == NULL) {
			cmd_list.head = createCmdNode(newWord);
		} else {
			/* skip to the end of the list */
			for (current = cmd_list.head; current->next != NULL; current =
					current->next)
				;
			current->next = createCmdNode(newWord);
		}
		return true;
	}
	return false;
}
/* reset table */
void resetCmdTable(void) {
	cmdNode* curr = NULL;
	cmd_list.length = MEMORY_START;
	while ((curr = cmd_list.head) != NULL) { /* set curr to head, stop if list empty. */
		cmd_list.head = cmd_list.head->next; /* advance head to next element. */
		free(curr); /* delete saved pointer. */
	}
}

/* print table */
void printCmdTable(void) {
	int lineNumber = MEMORY_START;
	cmdNode* curr = NULL;
	printf("#\tValue\n");
	for (curr = cmd_list.head; curr != NULL; curr = curr->next, lineNumber++) {
		printf("%s\t%s\n", base10to32enc(lineNumber),
				base10to32enc(curr->value.print));
	}
	printDataTable(cmd_list.length);
}

