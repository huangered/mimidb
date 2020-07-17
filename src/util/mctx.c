#include "util/mctx.h"

void* palloc(Size size) {
    return malloc(size);
}

void pfree(void* ptr) {
    free(ptr);
}