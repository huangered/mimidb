#ifndef _BUFMGR_H_
#define _BUFMGR_H_

#include "mimi.hpp"
#include "access/relcache.hpp"
#include "storage/block.hpp"
#include "storage/page.hpp"
#include "storage/buf_internals.hpp"
#include "storage/buf.hpp"
#include "util/hash.hpp"

extern int NBuffers;
extern char* BufferBlocks;
extern BufferDesc* BuffDesc;
extern Hash* bufHash;
extern BufferDesc* freeBuffDesc;

typedef void* Block;

#define BufferGetBlock(buffer)  (Block)(BufferBlocks + ((buffer) - 1) * BLKSZ)
#define BufferGetPage(buffer)   ((Page)BufferGetBlock(buffer))
#define GetBufferDesc(buf_id)   (&BuffDesc[buf_id])

// Init the buffer mgr, share mem alloc
extern void BufferInit();
extern Buffer ReadBuffer(Relation rel, ForkNumber forkNumber, BlockNumber blkno);
extern void ReleaseBuffer(Buffer buffer);
extern void FlushBuffer(BufferDesc* buffDesc);

// for debug
extern void print_bufflist();
#endif // !_BUFMGR_H_
