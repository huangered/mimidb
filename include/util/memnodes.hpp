#ifndef _memnodes_hpp_
#define _memnodes_hpp_

typedef struct MemoryContextMethods {
    void* (*alloc)(MemoryContext context, Size size);
    void (*free_p)(MemoryContext context, void* pointer);
    void (*delete_context)(MemoryContext context);
} MemoryContextMethods;

typedef struct MemoryContextData {
    int type;
    bool isReset;
    bool allowInCritSection;
    MemoryContextMethods* methods;
    MemoryContext parent;
    MemoryContext firstchild;
    MemoryContext prevchild;
    MemoryContext nextchild;
    char* name;
} MemoryContextData;

#endif