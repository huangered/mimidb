#include "util/list.h"
#include "util/mctx.h"

List* new_list(char* value, int size) {
	List* newlist = palloc(offsetof(List, elements) +
		size * sizeof(ListCell));
	//newlist->type = type;
	newlist->length = 1;
	newlist->elements[0].value = value;
	return newlist;
}

List*
append_list(List* list, char* cell) {

	int len = list->length;
	list->elements[len].value = cell;
	list->length += 1;
	return list;
}
