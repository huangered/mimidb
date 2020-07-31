#ifndef _BUFMGR_H_
#define _BUFMGR_H_

#include "mimi.h"
#include "access/rel.h"
#include "storage/block.h"
#include "storage/page.h"

typedef int Buffer;

static Page page;

#define BufferGetBlock(buffer)  page[buffer]
#define BufferGetPage(buffer)   ((Page)BufferGetBlock(buffer))

// Init the buffer mgr, share mem alloc
extern void BufferInit();
extern Buffer ReadBuffer(Relation rel, ForkNumber forkNumber, BlockNum blkno);
extern void ReleaseBuffer(Buffer buffer);

#endif // !_BUFMGR_H_
