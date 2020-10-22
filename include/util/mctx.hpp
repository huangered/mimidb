#ifndef _MCTX_H_
#define _MCTX_H_

#include "c.hpp"

void MemoryContextInit();

void* palloc(Size size);
void pfree(void* ptr);

#endif // !_MCTX_H_
