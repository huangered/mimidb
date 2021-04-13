#ifndef _buf_internal_hpp_
#define _buf_internal_hpp_

#include "mimi.hpp"
#include "access/relcache.hpp"
#include "storage/block.hpp"
#include "storage/page.hpp"
#include "storage/buf.hpp"
#include "util/hashmap.hpp"

class BufferMgr
{
private:
	char* _blocks;
	HashMap<BufferTag, Buffer> _hashMap;
	BufferDesc* _buffDesc;
	BufferDesc* _freeBuffDesc;
        //int index;
public:
	BufferMgr();
	~BufferMgr();

	// Read MAIN_FORK 
	Buffer ReadBuffer(Relation rel, BlockNumber block);
	Buffer ReadBufferExtend(Relation rel, ForkNumber fork, BlockNumber block);

	void ReleaseBuffer(Buffer buffer);
	void FlushBuffer(BufferDesc* buffDesc);
	BufferDesc* GetBufferDesc(Buffer buffer);
	Page GetPage(Buffer bufId);
	void MarkBufferDirty(Buffer bufId);
private:
	Buffer _ReadBufferCommon(Relation rel, ForkNumber fork, BlockNumber block);
	BufferDesc* _BufferAlloc(Relation rel, ForkNumber forkNumber, BlockNumber blkno, bool* found);
	Buffer _FindFreeBuffer();
};

#endif
