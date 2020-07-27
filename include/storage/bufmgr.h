#ifndef _BUFMGR_H_
#define _BUFMGR_H_

#include "mimi.h"
#include "access/rel.h"
#include "storage/block.h"
#include "storage/page.h"

typedef uint16 Buffer;

static char* mockBuf = NULL;

#define BufferGetBlock(buffer)  mockBuf
#define BufferGetPage(buffer)   ((Page)BufferGetBlock(buffer))

extern Buffer ReadBuffer(Relation rel, ForkNumber forkNumber, BlockNum blkno);
extern void ReleaseBuffer(Buffer buffer);

#endif // !_BUFMGR_H_
