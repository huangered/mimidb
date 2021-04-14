#ifndef _list_hpp_
#define _list_hpp_

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

#define list_len(l)			(l->length)
#define list_first_elem(l)	(l->head)
#define list_next_elem(l)	(l->next)

extern List* new_list(NodeTag tag);
extern List* append_list(List* list, void* value);
#endif