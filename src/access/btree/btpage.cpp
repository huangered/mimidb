#include "access/btree.hpp"
#include "storage/indexfsm.hpp"
#include <assert.h>

BTreeMetaData*
BtreeIndex::_bt_getmeta(Relation rel, Buffer metabuf) {
    Page metap           = BufferGetPage(metabuf);
    BTreeMetaData* metad = (BTreeMetaData*)PageGetContent(metap);
    return metad;
}

/*
update the metapage and save to disk.
*/
void
BtreeIndex::_bt_updatemeta(Buffer metabuf) {
}

/*
Get the relation root page buffer

1. load the relation cache block num.
2. if the cache is empty , load from meta page.
3. if block num is null in meta, create new root.
 */
Buffer
BtreeIndex::_bt_get_root(Relation rel) {
    Buffer metabuf;
    Page metapage;
    Buffer rootbuf;
    BTreeMetaData* metad;
    BlockNumber rootblkno;
    Page rootpage;

    // 从 meta 缓存里获取 root buf
    if (rel->rd_metacache != nullptr) {
        metad = (BTreeMetaData*)rel->rd_metacache;
        assert(metad->btm_root != P_NONE);

        rootbuf = _bt_get_buf(rel, metad->fastroot);
        return rootbuf;
    }

    // 从 blocknum 0 加载 meta
    metabuf                              = _bt_get_buf(rel, BTREE_METAPAGE);
    metapage                             = BufferGetPage(metabuf);
    metad                                = (BTreeMetaData*)PageGetContent(metapage);
    PageGetHeader(metapage)->pd_checksum = 12345;

    if (metad->btm_root == P_NONE) {
        // 如果meta没有初始化，初始化
        // 1. 创建root block
        rootbuf   = _bt_get_buf(rel, P_NEW);
        rootblkno = BufferGetBlockNumber(rootbuf);
        // 1.1 更新root block
        rootpage                 = BufferGetPage(rootbuf);
        BTreeSpecial rootspecial = (BTreeSpecial)PageGetSpecial(rootpage);
        rootspecial->btsd_next   = P_NONE;
        rootspecial->btsd_prev   = P_NONE;
        rootspecial->btsd_flags  = (BTP_LEAF | BTP_ROOT);

        // 2. 更新meta
        metad->btm_root = rootblkno;
        metad->fastroot = rootblkno;

        MarkBufferDirty(rootbuf);
        MarkBufferDirty(metabuf);
        // 释放metabuf
        ReleaseBuffer(metabuf);
    } else {
        // 如果meta初始化了
        rootblkno         = metad->fastroot;
        rel->rd_metacache = metad;
        rootbuf           = _bt_get_buf(rel, rootblkno);
    }

    return rootbuf;
}

Buffer
BtreeIndex::_bt_get_buf(Relation rel, BlockNumber blkno) {
    Buffer buf;
    if (blkno != P_NEW) {
        buf = ReadBuffer(rel, blkno);
    } else {
        // create new block for cbtree
        blkno     = GetFreeIndexPage(rel);
        buf       = ReadBuffer(rel, blkno);
        Page page = BufferGetPage(buf);
        _bt_init_page(page);
    }
    return buf;
}

void
BtreeIndex::_bt_relbuf(Relation rel, Buffer buf) {
    ReleaseBuffer(buf);
}
