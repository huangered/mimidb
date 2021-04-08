#ifndef _memctx_hpp_
#define _memctx_hpp_

#include "c.hpp"

void* palloc(Size size);
void pfree(void* ptr);

#endif // !_MCTX_H_
