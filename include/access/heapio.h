/*
 * heap 的基本输入/输出方法定义
 */
#ifndef _heapio_hpp_
#define _heapio_hpp_

#include "access/heaptuple.h"
#include "storage/buf.h"
#include "access/rel.h"

void RelationPutHeapTuple(Relation rel, Buffer buffer, HeapTuple tuple);
Buffer RelationGetBufferForTuple(Relation rel, Size len);

#endif
