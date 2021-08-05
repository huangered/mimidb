#include "c_util/cvector.h"
#include <stdlib.h>
#include <memory.h>
Vector*
vector_new() {
    Vector* vec = malloc(sizeof(Vector));
    vec->len    = 0;
    vec->maxlen = 2;
    vec->arr    = malloc(2 * sizeof(vectorItem));
    memset(vec->arr, 0, 2 * sizeof(vectorItem));
    return vec;
}

Vector*
vector_insert(Vector* list, size_t index, void* value) {
    return list;
}

Vector*
vector_add(Vector* list, void* value) {
    if (list->len == list->maxlen) {
        vector_resize(list, list->maxlen * 2);
    }
    vector_index(list, list->len) = value;
    list->len += 1;
    return list;
}

Vector*
vector_add_int(Vector* list, int value) {
    if (list->len == list->maxlen) {
        vector_resize(list, list->maxlen * 2);
    }
    vector_index_int(list, list->len) = value;
    list->len += 1;
    return list;
}

Vector*
vector_remove(Vector* list, size_t index) {
    return list;
}

Vector*
vector_resize(Vector* vec, size_t nsize) {
    vectorItem* arr = malloc(nsize * sizeof(vectorItem));
    memcpy(arr, vec->arr, vec->len * sizeof(vectorItem));
    memset(arr + nsize - vec->len, 0, nsize - vec->len);

    free(vec->arr);
    vec->arr    = arr;
    vec->maxlen = nsize;
    return vec;
}

void
vector_free(Vector* vec) {
    free(vec->arr);
    free(vec);
}