#ifndef _LIST_H_
#define _LIST_H_

#include "mimi.h"
#include "node/node.h"

typedef struct ListCell {
	union {
		int int_value;
		void* ptr_value;
	} data;
	struct ListCell* next;
} ListCell;

typedef struct List {
	NodeTag type;
	int length;
	ListCell* head;
} List;

#define list_len(l)	(l->length)

extern List* new_list(NodeTag tag);
extern List* append_list(List* list, void* value);
#endif