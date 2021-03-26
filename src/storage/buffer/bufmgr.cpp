#include "storage/bufmgr.hpp"
#include "storage/buf_internal.hpp"

BufferMgr _mgr;

Buffer ReadBuffer(Relation rel, BlockNumber block) {
	return _mgr.ReadBuffer(rel, block);
}

Buffer ReadBufferExtend(Relation rel, ForkNumber fork, BlockNumber block) {
	return _mgr.ReadBufferExtend(rel, fork, block);
}

void ReleaseBuffer(Buffer buffer) {
	_mgr.ReleaseBuffer(buffer);
}

BufferDesc* GetBufferDesc(Buffer buffer) {
	return _mgr.GetBufferDesc(buffer);
}
Page BufferGetPage(Buffer bufId) {
	return _mgr.GetPage(bufId);
}
void MarkBufferDirty(Buffer bufId) {
	_mgr.MarkBufferDirty(bufId);
}
