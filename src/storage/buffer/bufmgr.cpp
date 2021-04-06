#include "storage/bufmgr.hpp"
#include "storage/buf_internal.hpp"

BufferMgr* bmgr = new BufferMgr{};

Buffer
ReadBuffer(Relation rel, BlockNumber block) {
	return bmgr->ReadBuffer(rel, block);
}

Buffer
ReadBufferExtend(Relation rel, ForkNumber fork, BlockNumber block) {
	return bmgr->ReadBufferExtend(rel, fork, block);
}

void
ReleaseBuffer(Buffer buffer) {
	bmgr->ReleaseBuffer(buffer);
}

BufferDesc*
GetBufferDesc(Buffer buffer) {
	return bmgr->GetBufferDesc(buffer);
}

Page
BufferGetPage(Buffer buffer) {
	return bmgr->GetPage(buffer);
}

void
MarkBufferDirty(Buffer buffer) {
	bmgr->MarkBufferDirty(buffer);
}
