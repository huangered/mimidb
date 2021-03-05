#ifndef _buf_internals_h_
#define _buf_internals_h_

#include "storage/buf.hpp"

/* freelist.c */
extern void StrategyInitialize();
extern Buffer StrategyGetBuffer();
extern void StrategyFreeBuffer(Buffer buffer);

#endif // !_buf_internals_h_
