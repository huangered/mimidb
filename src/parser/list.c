#include "node/list.h"

List*
new_list(NodeTag type) {
    List* newlist   = malloc(sizeof(List));
    newlist->type   = type;
    newlist->length = 0;
    newlist->head   = 0;
    return newlist;
}

List*
append_list(List* list, void* cell) {

    ListCell* new_head;

    new_head                 = malloc(sizeof(List));
    new_head->next           = list->head;
    new_head->data.ptr_value = cell;
    list->head               = new_head;
    list->length += 1;
    return list;
}
