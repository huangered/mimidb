#ifndef _memutils_hpp_
#define _memutils_hpp_

#include "mimi.hpp"
#include "util/memnodes.hpp"

#define MAXIMUM_ALIGNOF          8
#define TYPEALIGN(ALIGNVAL, LEN) (((uintptr_t)(LEN) + ((ALIGNVAL)-1)) & ~((uintptr_t)((ALIGNVAL)-1)))

#define MAXALIGN(LEN) TYPEALIGN(MAXIMUM_ALIGNOF, (LEN))

extern MemoryContext TopMemoryContext;

extern MemoryContext CurrentMemoryContext;
extern MemoryContext ErrorContext;

/* mctx.c */
extern void MemoryContextInit(void);
extern void MemoryContextDelete(MemoryContext context);
extern void MemoryContextDeleteChildren(MemoryContext context);
extern void MemoryContextStats(MemoryContext context);
extern void MemoryContextStatsDetail(MemoryContext context);
extern void MemoryContextSetParent(MemoryContext content, MemoryContext new_parent);
extern MemoryContext MemoryContextCreate(int tag, Size size, MemoryContextMethods* methods, MemoryContext parent,
                                         const char* name);

/* aset.c */
extern MemoryContext AllocSetContextCreate(MemoryContext parent, const char* name, Size minContextSize,
                                           Size initBlockSize, Size maxBlockSize);
#endif