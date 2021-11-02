#ifndef _bufmgr_hpp_
#define _bufmgr_hpp_

#include "access/relation.hpp"
#include "storage/page.hpp"
#include "storage/buf.hpp"
#include "storage/buf_internal.hpp"

extern int NBuffers;
/* in buf_internal.cpp */
extern char* BufferBlocks;

typedef void* Block;

#define P_NEW INVALID_BLOCK /* the tag to create new page */

#define BufferIsValid(bufnum) ((bufnum) < NBuffers && (bufnum) != 0)
#define BufferGetBlock(buffer) (Block)(BufferBlocks + ((buffer) -1)*BLKSZ)
#define BufferGetPage(buffer) ((Page)BufferGetBlock(buffer))

Buffer ReadBuffer(Relation rel, BlockNumber block);
Buffer ReadBufferExtend(Relation rel, ForkNumber fork, BlockNumber block);
void LockBuffer(Buffer buf, int mode);
void ReleaseBuffer(Buffer buffer);
void MarkBufferDirty(Buffer buffer);
BlockNumber BufferGetBlockNumber(Buffer buffer);
void FlushOneBuffer(Buffer buffer);

// buf_init.cpp
extern void InitBufferPool(void);

#endif // !_BUFMGR_H_
