#ifndef _buf_internals_h_
#define _buf_internals_h_

#include "storage/buf.hpp"

/* freelist.c */
class BufferStrategy {
private:
	BufferMgr* _bufMgr;
public:
	Buffer GetBuffer();
	void FreeBuffer(Buffer buffer);
};
#endif // !_buf_internals_h_
