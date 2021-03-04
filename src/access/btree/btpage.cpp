#include "access/btree.hpp"
#include "storage/indexfsm.hpp"



BTreeMetaData* BtreeIndex::_bt_getmeta(Relation rel, Buffer metabuf) {
    Page metap = _bufMgr->GetPage(metabuf);
    BTreeMetaData* metad = (BTreeMetaData*)PageGetContent(metap);
    return metad;
}

/*
update the metapage and save to disk.
*/
void BtreeIndex::_bt_updatemeta(Buffer metabuf) {

}

/*
Get the relation root page buffer

1. load the relation cache block num.
2. if the cache is empty , load from meta page.
3. if block num is null in meta, create new root.
 */
Buffer BtreeIndex::_bt_get_root(Relation rel) {
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
        Page page = _bufMgr->GetPage(rootbuf);
        _bt_init_page(page);
        BTreeSpecial special = (BTreeSpecial)PageGetSpecial(page);
        special->flags = BTP_ROOT | BTP_LEAF;

        rel->root_blkno = _bufMgr->GetBufferDesc(rootbuf)->tag.blockNum;
        _bt_updatemeta(metabuf);
    }
    else {
        rootbuf = _bt_get_buf(rel, blkno);
    }
    return rootbuf;
}

Buffer BtreeIndex::_bt_get_buf(Relation rel, BlockNumber blkno) {
    Buffer buf;
    if (blkno != P_NEW) {
        buf = _bufMgr->ReadBuffer(rel, MAIN_FORKNUM, blkno);
    }
    else {
        // create new block for cbtree
        blkno = GetFreeIndexPage(rel);
        buf = _bufMgr->ReadBuffer(rel, MAIN_FORKNUM, blkno);
        Page page = _bufMgr->GetPage(buf);
        _bt_init_page(page);
    }
    return buf;
}