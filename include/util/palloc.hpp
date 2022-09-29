#ifndef _palloc_hpp_
#define _palloc_hpp_

typedef struct MemoryContextData* MemoryContext;

extern void* MemoryContextAlloc(MemoryContext context, Size size);
extern void* palloc(Size size);
extern void* palloc0(Size size);
extern void pfree(void* ptr);

#endif
