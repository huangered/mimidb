#include "util/mctx.hpp"

void* palloc(Size size) {
    return std::malloc(size);
}

void pfree(void* ptr) {
    std::free(ptr);
}