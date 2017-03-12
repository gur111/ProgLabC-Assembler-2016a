#ifndef DATA_H
#define DATA_H

#include <stdio.h>      /* NULL */
#include <stdlib.h>     /* malloc*/

/*###############CONSTANTS##################*/
#define MAX_VALUE
/*###############STRUCTURES#################*/
typedef struct dataNode {
	unsigned int value;
	struct dataNode* next;
} dataNode;

typedef struct {
	dataNode* head;
	int length;
} dataList;

/*############EXTERN VARIABLES#############*/
extern dataList data_list;
/*############FUNCTIONS####################*/
/* 
 Adds data (char or int) to data list
 */
int addData(unsigned int);
/* return the length of cmd_list */
int getDataLength(void);
/* reset data table */
void resetDataTable(void);
/* print table */
void printDataTable(int lineNumber);

#endif
