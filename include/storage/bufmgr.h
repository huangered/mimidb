#ifndef _BUFMGR_H_
#define _BUFMGR_H_

#include "mimi.h"
#include "access/rel.h"
#include "storage/block.h"

typedef uint16 Buffer;

extern Buffer ReadBuffer(Relation rel, BlockNum blkno);
extern void ReleaseBuffer(Buffer buffer);

#endif // !_BUFMGR_H_
