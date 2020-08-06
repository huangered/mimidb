#ifndef _BUFMGR_H_
#define _BUFMGR_H_

#include "mimi.h"
#include "access/rel.h"
#include "storage/block.h"
#include "storage/page.h"
#include "storage/buf_internals.h"

typedef int Buffer;

extern char* BufferBlocks;
extern BufferDesc* buffDesc;

#define BufferGetBlock(buffer)  (BufferBlocks + buffer * BLKSZ)
#define BufferGetPage(buffer)   ((Page)BufferGetBlock(buffer))
#define GetBufferDesc(buf_id)  (buffDesc + buf_id)

// Init the buffer mgr, share mem alloc
extern void BufferInit();
extern Buffer ReadBuffer(Relation rel, ForkNumber forkNumber, BlockNum blkno);
extern void ReleaseBuffer(Buffer buffer);

#endif // !_BUFMGR_H_
