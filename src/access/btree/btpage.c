#include "access/btree.h"
#include "storage/indexfsm.h"
#include <assert.h>

struct BTreeMetaData*
_bt_getmeta(Relation rel, Buffer metabuf) {
    Page metap                  = BufferGetPage(metabuf);
    struct BTreeMetaData* metad = (struct BTreeMetaData*)PageGetContent(metap);
    return metad;
}

/*
 * update the metapage and save to disk.
 */
void
_bt_updatemeta(Buffer metabuf) {
}

/*
 * Get the relation root page buffer
 *
 * 1. load the relation cache block num.
 * 2. if the cache is empty , load from meta page.
 * 3. if block num is null in meta, create new root.
 */
Buffer
_bt_get_root(Relation rel) {
    Buffer metabuf;
    Page metapage;
    Buffer rootbuf;
    struct BTreeMetaData* metad;
    BlockNumber rootblkno;
    Page rootpage;

    // 从 meta 缓存里获取 root buf
    if (rel->rd_metacache != NULL) {
        metad = (struct BTreeMetaData*)rel->rd_metacache;
        assert(metad->btm_root != P_NONE);

        rootbuf = _bt_get_buf(rel, metad->btm_fastroot);
        return rootbuf;
    }

    // 从 blocknum 0 加载 meta
    metabuf                              = _bt_get_buf(rel, BTREE_METAPAGE);
    metapage                             = BufferGetPage(metabuf);
    metad                                = (struct BTreeMetaData*)PageGetContent(metapage);
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
        metad->btm_root     = rootblkno;
        metad->btm_fastroot = rootblkno;

        MarkBufferDirty(rootbuf);
        MarkBufferDirty(metabuf);
        // 释放metabuf
        ReleaseBuffer(metabuf);
    } else {
        // 如果meta初始化了
        rootblkno         = metad->btm_fastroot;
        rel->rd_metacache = metad;
        rootbuf           = _bt_get_buf(rel, rootblkno);
    }

    return rootbuf;
}

Buffer
_bt_get_buf(Relation rel, BlockNumber blkno) {
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
_bt_relbuf(Relation rel, Buffer buf) {
    ReleaseBuffer(buf);
}
