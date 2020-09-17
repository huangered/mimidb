#ifndef _LIST_H_
#define _LIST_H_

#include "mimi.h"
#include "node/node.h"

typedef union ListCell {
	void* ptr_value;
	int int_value;
	Oid oid_value;
} ListCell;

typedef struct List {
	NodeTag type;
	int length;
	ListCell elements[];
} List;

extern List* new_list(NodeTag type, int size);

#endif