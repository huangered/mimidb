#ifndef _MCTX_H_
#define _MCTX_H_

#include "c.h"

void* palloc(Size size);
void pfree(void* ptr);

#endif // !_MCTX_H_
