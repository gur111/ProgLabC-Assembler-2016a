/*
 * symbolTable.c
 *
 *  Created on: Feb 5, 2016
 *      Author: Gur
 */

#include "assembler.h"
#include "symbolTable.h"
#include "symbolStructs.h"
#include "converter.h"

static label *createLabel(char *labelName, int address, bool isExtertan,
		bool isOperation);
static labelNode *createLabelNode(label *thisLabel, labelNode *nextNode);

/* The list */
labelList symbol_list = { NULL };

/* Extern and Entry addresses list */
static externList ext_list = { NULL };
static entryList ent_list = { NULL };

/** Adds a new label to the symbol table.
 *
 * @return status of errors.
 * @populate the errMsg with errors if exist
 */
bool addLabel(char *labelName, int address, bool isExt, bool isOp) {
	labelNode *newLabel;
	labelNode *current = symbol_list.head;

	/* Some error checking */
	if (labelName == NULL){
		error(sprintf(errMsg, LABEL_NAME_ERR));
		return false;
	}
	while (current) {/* Makes sure the label doesn't exist already */
		if (strcmp(current->this->labelName, labelName) == 0) { /* True is label exists */
			error(sprintf(errMsg, MULTI_LABEL_DEF, labelName));
			return false;
		} else if (current->next) {
			current = current->next;
		} else
			break;
	}

	/* Adds the label to the location found as the right one */
	newLabel = createLabelNode(createLabel(labelName, address, isExt, isOp),
	NULL);
	if (newLabel == NULL)
		return false; /* Return false if out of RAM */

	if (!symbol_list.head)
		symbol_list.head = newLabel;
	else
		current->next = newLabel;
	return true;
}/* End addLabel */

/* Register an external flag in a list */
bool addExt(char *symbol, int address) {
	externNode *node = ext_list.head;

	if (!node && !(node = malloc(sizeof(node)))) {
		error(sprintf(errMsg, OUT_OF_RAM));
		return false;
	}
	if (ext_list.head != NULL) {
		while (node->next)/* Skip to the end */
			node = node->next;
		if (!(node->next = malloc(sizeof(node)))) {
			error(sprintf(errMsg, OUT_OF_RAM));
			return false;
		}
		node = node->next;
	} else {
		ext_list.head = node;
	}
	copyStr(&node->this.labelName, symbol);
	node->this.address = address + MEMORY_START;
	node->next = NULL;
	return true;
} /* End addExt */

/* Register an external flag in a list */
bool addEnt(label *lbl) {
	entryNode *node = ent_list.head;

	if (!node && !(node = malloc(sizeof(node)))) {
		error(sprintf(errMsg, OUT_OF_RAM));
		return false;
	}
	if (ent_list.head != NULL) {
		while (node->next)/* Skip to the end */
			node = node->next;
		if (!(node->next = malloc(sizeof(node)))) {
			error(sprintf(errMsg, OUT_OF_RAM));
			return false;
		}
		node = node->next;
	} else {
		ent_list.head = node;
	}
	node->this.labelName = lbl->labelName;
	node->this.address = lbl->address;
	node->next = NULL;
	return true;
} /* End addEnt */

/* Pops an extern reference and removes it from the list */
char *popExt(int *address) {
	externNode *node = ext_list.head;
	char *labelName;
	if (!node)
		return NULL;
	ext_list.head = node->next;
	*address = node->this.address;
	labelName = node->this.labelName;
	free(node);
	return labelName;
} /* End popExt */

/* Pops an extern reference and removes it from the list */
char *popEnt(int *address) {
	entryNode *node = ent_list.head;
	char *labelName;
	if (!node)
		return NULL;
	ent_list.head = node->next;
	*address = node->this.address;
	labelName = node->this.labelName;
	free(node);
	return labelName;
} /* End popEnt */

/* Fix all relocatable */
void relocate(int paddin) {
	labelNode *node = symbol_list.head;
	if (node) {
		do {
			if (!node->this->isOp && !node->this->isExt) {
				node->this->address += paddin;
			}
		} while ((node = node->next));
	}
}/* End relocate */

/* Gets a random address of a non external symbol */
int getRandomAddress(void) {
	labelNode *node = symbol_list.head;
	int i = 0;

	if (node) {
		do {/* Counts the non external labels */
			if (!node->this->isExt)
				i++;
		} while ((node = node->next));
		if (!i)
			return -1;
		i = rand() % i;
		node = symbol_list.head;

		while (i-- || node->this->isExt) {/* Skip to the random label */
			if (node->this->isExt)
				i++;
			node = node->next;
		}
		return node->this->address;
	}

	return -1;
}/* End getRandomAddress */

/* Searches the symbol table for the name given */
bool findLabel(const char *name) {
	return getLabel(name) ? true : false;
}/* End firstLabel */

/* Returns the requested label to the user. NULL if does not exist */
label *getLabel(const char *name) {
	labelNode *node = symbol_list.head;
	do {
		if (strcmp(node->this->labelName, name) == 0)
			return node->this;
	} while ((node = node->next) != NULL);
	return NULL;
}/* End getLabel */

/* Free all the elements in the symbol table */
void freeSymbolTable(void) {
	labelNode *node = symbol_list.head;
	if (node != NULL) {
		do {
			symbol_list.head = node->next;
			free(node->this->labelName);
			free(node->this);
			free(node);
		} while ((node = node->next) != NULL);
		symbol_list.head = NULL;
	}
}/* End freeSymbolTable */

void printSymbolTable(void) {/* Debug only. */
	labelNode *node = symbol_list.head;
	printf("%s\t\t%s\t\t%s\t%s\n", "Label", "Address", "isExtern", "isOp");
	if (node) {
		do {
			printf("%s\t\t%s\t\t%d\t\t%d\n", node->this->labelName,
					base10to32enc(node->this->address), node->this->isExt,
					node->this->isOp);
		} while ((node = node->next) != NULL);
	}

}/* End printSymbolTable */

/* ~-~-~-~ PRIVATE FUNCTIONS ~-~-~-~ */

/* Creates a label with a dynamic allocated storage
 *
 * @return NULL for errors.
 */
static label *createLabel(char *labelName, int address, bool isExt, bool isOp) {
	label *newLabel = malloc(sizeof(label));
	if (newLabel == NULL) {
		error(sprintf(errMsg, OUT_OF_RAM));
		return NULL;
	}

	if (!copyStr(&newLabel->labelName, labelName)) {
		free(newLabel);
		error(sprintf(errMsg, OUT_OF_RAM));
		return NULL;
	}
	newLabel->address = address;
	newLabel->isExt = isExt;
	newLabel->isOp = isOp;
	return newLabel;
}/* End createLabel */

/* Creates a label node with a dynamic allocated storage
 *
 * @return NULL for errors.
 */
static labelNode *createLabelNode(label *this, labelNode *next) {
	labelNode *newLabelNode = malloc(sizeof(labelNode));
	if (newLabelNode == NULL || this == NULL) {
		if (this)
			free(this->labelName);
		free(this);
		free(newLabelNode);
		error(sprintf(errMsg, OUT_OF_RAM));
		return NULL;
	}

	newLabelNode->this = this;
	newLabelNode->next = next;
	return newLabelNode;
}/* End createLabelNode */
