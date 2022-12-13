#ifndef _mm_list_h_
#define _mm_list_h_

#include "node/node.h"

typedef struct ListCell ListCell;

typedef struct List {
    NodeTag type;
    int length;
    ListCell* head;
    ListCell* tail;
} List;

struct ListCell {
    union {
        int int_value;
        void* ptr_value;
        Oid oid_values;
    } data;
    ListCell* next;
};

#define list_len(l)        (l->length)
#define list_first_elem(l) (l->head)
#define list_next_elem(l)  (l->next)

extern ListCell* list_head(List* l);
extern ListCell* list_tail(List* l);
extern int list_length(List* l);

List* list_new();
void list_free(List* list);
List* list_add(List* list, void* value);
List* list_add_int(List* list, int value);
List* list_delete(List* list, void* value);

#endif