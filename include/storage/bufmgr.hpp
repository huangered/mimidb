#ifndef _BUFMGR_H_
#define _BUFMGR_H_

#include "mimi.hpp"
#include "access/relcache.hpp"
#include "storage/block.hpp"
#include "storage/page.hpp"
#include "storage/buf_internals.hpp"
#include "storage/buf.hpp"
#include "util/hashmap.hpp"

class BufferMgr
{
private:
	const int SIZE = 20;
	HashMap<BufferTag, Buffer>* _hashMap;

	char* _blocks;
	BufferDesc* _buffDesc;
	BufferDesc* _freeBuffDesc;
public:
	BufferMgr();
	~BufferMgr();
	BufferMgr(const BufferMgr&) = delete;
	BufferMgr& operator=(BufferMgr) = delete;

	Buffer ReadBuffer(Relation rel, ForkNumber fork, BlockNumber block);
	void ReleaseBuffer(Buffer buffer);
	void FlushBuffer(BufferDesc* buffDesc);
	BufferDesc* GetBufferDesc(Buffer buffer);
	char* GetPage(Buffer bufId);

private:
	BufferDesc* BufferAlloc(Relation rel, ForkNumber forkNumber, BlockNumber blkno);
	void load_page(BufferTag tag, Buffer buf);

};

#endif // !_BUFMGR_H_
