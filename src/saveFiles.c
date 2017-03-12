#include "cmdTable.h"
#include "dataTable.h"
#include "assembler.h"
#include "converter.h"
#include "symbolStructs.h"
#include <string.h>

/* Prototypes */
static bool saveObj(FILE *file, int *i);
static bool saveData(FILE *file, int *i);
static bool saveExt(FILE *file, int *i);
static bool saveEnt(FILE *file, int *i);

/* Saves the files for successful assembling */
void saveFiles(void) {
	char *name;
	FILE *out;
	bool keep;
	int i = MEMORY_START;

	copyStr(&name, currFileName);

	name[strlen(name) - EXT_LEN + 1] = '\0';
	strcat(name, OBJ_EXT);
	out = fopen(name, "w");
	keep = saveObj(out, &i);
	fclose(out);
	if (!keep)
		remove(name);

	name[strlen(name) - EXT_LEN + 1] = '\0';
	strcat(name, EXT_EXT);
	keep = true;

	out = fopen(name, "w");
	keep = saveExt(out, &i);
	fclose(out);
	if (!keep)
		remove(name);

	keep = true;
	name[strlen(name) - EXT_LEN] = '\0';
	strcat(name, ENT_EXT);
	out = fopen(name, "w");
	keep = saveEnt(out, &i);
	fclose(out);
	if (!keep)
		remove(name);
	free(name);
}

/* Saves commands to the file */
static bool saveObj(FILE *file, int *i) {
	cmdNode* cmd_node = NULL;
	int start = *i, cmdAmount = 0;
	cmd_node = cmd_list.head;
	if (cmd_node != NULL) {
		while (cmd_node != NULL) { /* Get the length because the .length is not actually the length but the address by now */
			cmd_node = cmd_node->next;
			cmdAmount++;
		}
	}
	fprintf(file, "%s\t%s\n", base10to32enc(cmdAmount),
			base10to32enc(data_list.length));
	for (cmd_node = cmd_list.head; cmd_node != NULL;
			cmd_node = cmd_node->next, (*i)++) {
		fprintf(file, "%s\t%s\n", base10to32enc(*i),
				base10to32enc(cmd_node->value.print));
	}
	if (saveData(file, i))
		return true;

	if (start == *i)
		return false;
	else
		return true;
}

/* Saves data to the file */
bool saveData(FILE *file, int *i) {
	dataNode* data_node = NULL;
	int start = *i;

	for (data_node = data_list.head; data_node != NULL;
			data_node = data_node->next, (*i)++) {
		fprintf(file, "%s\t%s\n", base10to32enc(*i),
				base10to32enc(data_node->value));
	}
	if (start == *i)
		return false;
	else
		return true;
}

/* Saves externals to the file */
bool saveExt(FILE *file, int *i) {
	char *name;
	int num;
	bool hasContent = false;

	while ((name = popExt(&num))) {
		fprintf(file, "%s\t%s\n", name, base10to32enc(num));
		free(name);
		hasContent = true;
	}
	return hasContent;
}

/* Saves entries to the file */
bool saveEnt(FILE *file, int *i) {
	char *name;
	int num;
	bool hasContent = false;

	while ((name = popEnt(&num))) {
		fprintf(file, "%s\t%s\n", name, base10to32enc(num));
		hasContent = true;
	}
	return hasContent;
}
