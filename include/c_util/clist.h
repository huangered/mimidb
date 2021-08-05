#ifndef _c_list_h_
#define _c_list_h_

typedef struct ListCell {
    union {
        int int_value;
        void* ptr_value;
    } data;
    struct ListCell* next;
} ListCell;

typedef struct List {
    int length;
    ListCell* head;
} List;

#define list_len(l)        (l->length)
#define list_first_elem(l) (l->head)
#define list_next_elem(l)  (l->next)

List* list_new();
void list_free(List* list);
List* list_add(List* list, void* value);
List* list_add_int(List* list, int value);
List* list_delete(List* list, void* value);

#endif