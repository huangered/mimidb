#include "util/list.h"
#include "util/mctx.h"

List* new_list(NodeTag type, int size) {
	List* newlist = palloc(offsetof(List, elements) +
		size * sizeof(ListCell));
	newlist->type = type;
	newlist->length = size;

	return newlist;
}