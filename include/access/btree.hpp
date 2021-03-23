#ifndef _BT_TREE_H_
#define _BT_TREE_H_

#include "mimi.hpp"
#include "access/offset.hpp"
#include "access/rel.hpp"
#include "storage/block.hpp"
#include "storage/bufmgr.hpp"
#include "access/scankey.hpp"
#include "access/amapi.hpp"

#define BTREE_METAPAGE  0

typedef struct BTreeMetaData {
    BlockNumber root;
    BlockNumber fastroot;
} BTreeMetaData;

typedef struct IndexTupleData {
    int ht_id;          // record heap tuple id
    int tuple_size;     // temporarily value;
    int key;
    // data part
} IndexTupleData;

typedef IndexTupleData* IndexTuple;

typedef struct BTreeSpecialData {
    BlockNumber block_next;
    BlockNumber block_prev;
    uint16 level;
    uint16 flags;
} BTreeSpecialData;

typedef BTreeSpecialData* BTreeSpecial;

typedef struct BTStackData {
    BlockNumber blkno;
    OffsetNumber offset;
    struct BTStackData* parent;
} BTStackData;

typedef BTStackData* BTStack;

typedef struct BTreeScanData {
    IndexTuple itup;
    Size itemsz;
    bool nextkey;
    int keysz;
    ScanKeyData scankeys[128];
} BTreeScanData;

typedef BTreeScanData* BTreeScan;

typedef struct BTreeSearchKeyData {
    int key;
} BTreeSearchKeyData;

typedef BTreeSearchKeyData* BTreeSearchKey;


/*
btbuildempty() -- build btree meta page
 */ 


#define P_NEW                   INVALID_BLOCK
#define P_NONE                  0
#define P_RIGHTMOST(special)    ((special)->block_next == P_NEW)


#define BTP_LEAF  ( 1 << 0 )
#define BTP_ROOT  ( 1 << 1 )
#define BTP_META  ( 1 << 2 )

#define IID_USE   ( 1 << 0 )
#define IID_DEL   ( 1 << 1 )

#define P_ISLEAF(special)       ((special->flags & BTP_LEAF) != 0 )
#define P_ISROOT(special)       ((special->flags & BTP_ROOT) != 0 )

#define P_HIKEY                 ((OffsetNumber) 1)
#define P_FIRSTKEY              ((OffsetNumber) 2)
#define P_FIRSTDATAKEY(special) (P_RIGHTMOST(special) ? P_HIKEY:P_FIRSTKEY)

#define BTreeTupleGetDownLink(itup) (itup->ht_id)

class BtreeIndex : public BaseIndex {
private:
    std::shared_ptr<BufferMgr> _bufMgr;
private:
    // methods in btpage.c
    void _bt_init_page(Page page);
    void _bt_init_metapage(Page page, BlockNumber rootblkno);
    Buffer _bt_get_root(Relation rel);
    Buffer _bt_get_buf(Relation rel, BlockNumber blkno);
    Buffer _bt_newroot(Relation rel, Buffer lbuf, Buffer rbuf);
    Buffer _bt_moveright(Relation rel, BTreeScan key, Buffer buf);
    Buffer _bt_relandgetbuf(Relation rel, Buffer obuf, BlockNumber blkno);
    void _bt_relbuf(Relation rel, Buffer buf);

    // methods in btsearch.c
    bool _bt_first(IndexScanDesc scan);
    bool _bt_next(IndexScanDesc scan);
    OffsetNumber _bt_binsrch(Relation rel, Page page, BTreeScan key);
    OffsetNumber _bt_findinsertloc(Relation rel, Buffer buffer, BTreeScan key);

    // insert
    bool _bt_do_insert(Relation rel, IndexTuple itup);
    BTStack _bt_search(Relation rel, BTreeScan itup_key, Buffer* bufp);

    bool _bt_addtup(Page page, Item item, Size itemsz, OffsetNumber newitemoffset);
    void _bt_insertonpg(Relation rel, Buffer buffer, OffsetNumber newitemoffset, BTreeScan itup_key, BTStack stack);
    void _bt_insert_parent(Relation rel, Buffer lbuf, Buffer rbuf, BTStack stack, bool is_root);

    BTreeMetaData* _bt_getmeta(Relation rel, Buffer metabuf);
    void _bt_updatemeta(Buffer metabuf);

    // btsplit.c
    OffsetNumber _bt_find_split_offset(Buffer buf);
    Buffer _bt_split(Relation rel, IndexTuple itup, Buffer buf, OffsetNumber newitemoff);

    // btcompare.c
    int _bt_compare(Relation rel, BTreeScan key, Page page, OffsetNumber offset);

    // methods in btutils.c
    IndexTuple _bt_make_tuple(int key, int ht_id);
    BTreeScan _bt_make_scankey(Relation rel, IndexTuple itup);
    void _bt_freestack(BTStack stack);
public:
    BtreeIndex(std::shared_ptr<BufferMgr> bufMgr);
    virtual void buildempty(Relation rel);
    virtual bool insert(Relation rel, int key, int ht_id);
    virtual bool remove(Relation rel, int key);
    virtual bool gettuple(IndexScanDesc scan);
    virtual void vacuum(Relation rel);
};

#endif