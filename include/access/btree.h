#ifndef _BT_TREE_H_
#define _BT_TREE_H_

#include "mimi.h"
#include "access/offset.h"
#include "access/rel.h"
#include "storage/block.h"
#include "storage/bufmgr.h"
#include "access/scankey.h"
#include "access/amapi.h"

#define BTREE_METAPAGE  0

typedef struct BTreeMetaData {
    BlockNum root;
} BTreeMetaData;

typedef struct IndexTupleData {
    int ht_id;          // record heap tuple id
    int tuple_size;     // temporarily value;
    int key;
    // data part
} IndexTupleData;

typedef IndexTupleData* IndexTuple;

typedef struct BTreeSpecialData {
    BlockNum block_next;
    BlockNum block_prev;
    uint16 level;
    uint16 flags;
} BTreeSpecialData;

typedef BTreeSpecialData* BTreeSpecial;

typedef struct BTStackData {
    BlockNum blkno;
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
extern void btbuildempty(Relation rel);
extern bool btinsert(Relation rel, int key, int ht_id);
extern bool btremove(Relation rel, int key);
extern bool btgettuple(IndexScanDesc scan);
extern void btvacuum(Relation rel);

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


// methods in btpage.c
extern void _bt_init_page(Page page);
extern Buffer _bt_get_root(Relation rel);
extern Buffer _bt_get_buf(Relation rel, BlockNum blkno);
extern Buffer _bt_newroot(Relation rel, Buffer lbuf, Buffer rbuf);
extern Buffer _bt_moveright(Relation rel, BTreeScan key, Buffer buf);
extern Buffer _bt_relandgetbuf(Relation rel, Buffer obuf, BlockNum blkno);

// methods in btsearch.c
extern bool _bt_first(IndexScanDesc scan);
extern bool _bt_next(IndexScanDesc scan);
extern OffsetNumber _bt_binsrch(Relation rel, Page page, BTreeScan key);
extern OffsetNumber _bt_findinsertloc(Relation rel, Buffer buffer, BTreeScan key);

// insert
extern bool _bt_do_insert(Relation rel, IndexTuple itup);
extern BTStack _bt_search(Relation rel, BTreeScan itup_key, Buffer* bufp);

// btsplit.c
extern OffsetNumber _bt_find_split_offset(Buffer buf);
extern Buffer _bt_split(Relation rel, IndexTuple itup, Buffer buf, OffsetNumber newitemoff);

// btcompare.c
extern int _bt_compare(Relation rel, BTreeScan key, Page page, OffsetNumber offset);

// methods in btutils.c
extern IndexTuple _bt_make_tuple(int key, int ht_id);
extern BTreeScan _bt_make_scankey(Relation rel, IndexTuple itup);
extern void _bt_freestack(BTStack stack);

#endif