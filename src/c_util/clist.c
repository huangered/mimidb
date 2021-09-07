#include "c_util/clist.h"
#include <stdlib.h>

List*
list_new() {
    List* list   = malloc(sizeof(List));
    list->length = 0;
    list->head   = NULL;

    return list;
}

void
list_free(List* list) {
    while (list->head != NULL) {
        ListCell* cell = list->head;
        list->head     = cell->next;
        free(cell);
    }

    free(list);
}

List*
list_add(List* list, void* value) {
    ListCell* cell       = malloc(sizeof(ListCell));
    cell->data.ptr_value = value;
    cell->next           = list->head;

    list->length += 1;
    list->head = cell;
    return list;
}

List*
list_add_int(List* list, int value) {
    ListCell* cell       = malloc(sizeof(ListCell));
    cell->data.int_value = value;
    cell->next           = list->head;

    list->length += 1;
    list->head = cell;
    return list;
}

List*
list_delete(List* list, void* value) {
    return list;
}
