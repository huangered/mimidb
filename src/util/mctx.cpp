#include "util/mctx.hpp"

/*
 * 分配内存
 */
void*
palloc(Size size) {
    void* ptr = std::malloc(size);
    assert(ptr);
    return ptr;
}

/*
分配内存并置零
*/
void*
palloc0(Size size) {
    void* ptr = palloc(size);
    memset(ptr, 0, size);
    return ptr;
}

void
pfree(void* ptr) {
    std::free(ptr);
}