#ifndef _bufmgr_hpp_
#define _bufmgr_hpp_

#include "access/relation.hpp"
#include "storage/page.hpp"
#include "storage/buf.hpp"
#include "storage/buf_internal.hpp"

#define P_NEW INVALID_BLOCK

Buffer ReadBuffer(Relation rel, BlockNumber block);
Buffer ReadBufferExtend(Relation rel, ForkNumber fork, BlockNumber block);
void ReleaseBuffer(Buffer buffer);
BufferDesc* GetBufferDesc(Buffer buffer);
Page BufferGetPage(Buffer buffer);
void MarkBufferDirty(Buffer buffer);
BlockNumber BufferGetBlockNumber(Buffer buffer);
void FlushBuffer(Buffer buffer);

extern BufferMgr* bmgr;

#endif // !_BUFMGR_H_
