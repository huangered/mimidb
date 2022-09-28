#include "mimi.hpp"
#include "util/memutils.hpp"

#include <assert.h>
#include <string.h>

MemoryContext CurrentMemoryContext;

MemoryContext TopMemoryContext;
MemoryContext ErrorContext;

void*
palloc(Size size) {
    void* ret;

    ret = (*CurrentMemoryContext->methods->alloc)(CurrentMemoryContext, size);

    return ret;
}

void*
palloc0(Size size) {
    void* ptr = palloc(size);
    memset(ptr, 0, size);
    return ptr;
}
void
pfree(void* ptr) {
    (*CurrentMemoryContext->methods->free_p)(CurrentMemoryContext, ptr);
}

void
MemoryContextInit(void) {
    assert(TopMemoryContext == NULL);
    TopMemoryContext = AllocSetContextCreate(NULL, "Top", 0, 8 * 1024, 8 * 1024 * 1024);

    CurrentMemoryContext = TopMemoryContext;

    ErrorContext = AllocSetContextCreate(TopMemoryContext, "Error", 8 * 1024, 8 * 1024, 8 * 1024);
}

void
MemoryContextDelete(MemoryContext context) {
    assert(context != TopMemoryContext);
    MemoryContextDeleteChildren(context);
    // todo: set parent null
    MemoryContextSetParent(context, NULL);
    (*context->methods->delete_context)(context);
    pfree(context);
}

void
MemoryContextDeleteChildren(MemoryContext context) {
    while (context->firstchild != NULL)
        MemoryContextDelete(context->firstchild);
}

void
MemoryContextSetParent(MemoryContext context, MemoryContext new_parent) {
    if (new_parent == context->parent) {
        return;
    }

    /* 移除 */
    if (context->parent) {
        MemoryContext parent = context->parent;
        if (context->prevchild != NULL)
            context->prevchild->nextchild = context->nextchild;
        else {
            parent->firstchild = context->nextchild;
        }

        if (context->nextchild != NULL)
            context->nextchild->prevchild = context->prevchild;
    }
    /* 重新链接 */
    if (new_parent) {
        context->parent    = new_parent;
        context->prevchild = NULL;
        context->nextchild = new_parent->firstchild;
        if (new_parent->firstchild != NULL)
            new_parent->firstchild->prevchild = context;
        new_parent->firstchild = context;
    } else {
        context->parent    = NULL;
        context->prevchild = NULL;
        context->nextchild = NULL;
    }
}

void
MemoryContextStats(MemoryContext context) {
}

MemoryContext
MemoryContextCreate(int tag, Size size, MemoryContextMethods* methods, MemoryContext parent, const char* name) {
    MemoryContext node;
    Size needed = size + strlen(name) + 1;
    if (TopMemoryContext != NULL) {
        node = (MemoryContext)MemoryContextAlloc(TopMemoryContext, needed);
    } else {
        node = (MemoryContext)malloc(needed);
        assert(node != NULL);
    }

    memset(node, 0, size);
    node->type       = tag;
    node->methods    = methods;
    node->parent     = NULL; /* for the moment */
    node->firstchild = NULL;
    node->prevchild  = NULL;
    node->nextchild  = NULL;
    node->isReset    = true;
    node->name       = ((char*)node) + size;
    strcpy(node->name, name);

    if (parent) {
        node->parent    = parent;
        node->nextchild = parent->firstchild;
        if (parent->firstchild != NULL)
            parent->firstchild->prevchild = node;
        parent->firstchild = node;
    }

    return node;
}

void*
MemoryContextAlloc(MemoryContext context, Size size) {
    void* ret;

    ret = (*context->methods->alloc)(context, size);

    return ret;
}