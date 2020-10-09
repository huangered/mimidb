#ifndef _LIST_H_
#define _LIST_H_

#include "mimi.h"
#include "node/node.h"

typedef union ListCell {
	char* value;
} ListCell;

typedef struct List {
	NodeTag type;
	int length;
	ListCell elements[100];
} List;

extern List* new_list(char* value, int size);
extern List* append_list(List* list, char* value);
#endif