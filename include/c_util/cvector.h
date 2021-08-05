#ifndef _c_vector_h_
#define _c_vector_h_

#include <stddef.h>

typedef struct vectorItem {
    union {
        int int_value;
        void* ptr_value;
    } data;
} vectorItem;

typedef struct Vector {
    size_t len;
    size_t maxlen;
    struct vectorItem* arr;
} Vector;

#define vector_index(vec, n)     (vec->arr[n].data.ptr_value)
#define vector_index_int(vec, n) (vec->arr[n].data.int_value)

Vector* vector_new();
Vector* vector_insert(Vector* list, size_t index, void* value);
Vector* vector_add(Vector* list, void* value);
Vector* vector_add_int(Vector* list, int value);
Vector* vector_remove(Vector* list, size_t index);
Vector* vector_resize(Vector* vec, size_t nsize);
void vector_free(Vector* vec);
#endif