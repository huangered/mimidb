#ifndef _BUFMGR_HPP_
#define _BUFMGR_HPP_

#include "access/relation.hpp"
#include "storage/page.hpp"
#include "storage/buf.hpp"

Buffer ReadBuffer(Relation rel, BlockNumber block);
Buffer ReadBufferExtend(Relation rel, ForkNumber fork, BlockNumber block);
void ReleaseBuffer(Buffer buffer);
BufferDesc* GetBufferDesc(Buffer buffer);
Page BufferGetPage(Buffer buffer);
void MarkBufferDirty(Buffer buffer);

#endif // !_BUFMGR_H_
