#include "util/list.hpp"
#include "util/mctx.hpp"

List* new_list(NodeTag type) {
	List* newlist = (List*)palloc(sizeof(List));
	newlist->type = type;
	newlist->length = 0;
	newlist->head = NULL;
	return newlist;
}

List*
append_list(List* list, void* cell) {

	ListCell* new_head;

	new_head = (ListCell*)palloc(sizeof(ListCell));
	new_head->next = list->head;
	new_head->data.ptr_value = cell;
	list->head = new_head;
	list->length += 1;
	return list;
}
