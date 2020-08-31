#include "access/btree.h"
#include "storage/indexfsm.h"

static BTreeMetaData* _bt_getmeta(Relation rel, Buffer metabuf);
static void _bt_updatemeta(Buffer metabuf);

BTreeMetaData* _bt_getmeta(Relation rel, Buffer metabuf) {
    Page metap = BufferGetPage(metabuf);
    BTreeMetaData* metad = PageGetContent(metap);
    return metad;
}

/*
update the metapage and save to disk.
*/
void _bt_updatemeta(Buffer metabuf) {

}

/*
Get the relation root page buffer

1. load the relation cache block num.
2. if the cache is empty , load from meta page.
3. if block num is null in meta, create new root.
 */
Buffer _bt_get_root(Relation rel) {
    Buffer metabuf;
    Buffer rootbuf;
    BTreeMetaData* metad;

    // if no block number cache
    if (rel->root_blkno == P_NONE) {
        metabuf = _bt_get_buf(rel, BTREE_METAPAGE);
        metad = _bt_getmeta(rel, metabuf);
        rel->root_blkno = metad->root;
    }

    BlockNumber blkno = rel->root_blkno;
    if (blkno == P_NONE) {
        // init new page;
        rootbuf = _bt_get_buf(rel, P_NEW);
        Page page = BufferGetPage(rootbuf);
        _bt_init_page(page);
        BTreeSpecial special = (BTreeSpecial)PageGetSpecial(page);
        special->flags = BTP_ROOT | BTP_LEAF;

        rel->root_blkno = GetBufferDesc(rootbuf)->tag.blockNum;
        _bt_updatemeta(metabuf);
    }
    else {
        rootbuf = _bt_get_buf(rel, blkno);
    }
    return rootbuf;
}

Buffer _bt_get_buf(Relation rel, BlockNumber blkno) {
    Buffer buf;
    if (blkno != P_NEW) {
        buf = ReadBuffer(rel, MAIN_FORKNUMBER, blkno);
    }
    else {
        // create new block for cbtree
        blkno = GetFreeIndexPage(rel);
        buf = ReadBuffer(rel, MAIN_FORKNUMBER, blkno);
        Page page = BufferGetPage(buf);
        _bt_init_page(page);
    }
    return buf;
}