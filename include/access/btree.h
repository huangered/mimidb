#ifndef _bt_TREE_H_
#define _bt_TREE_H_

#include "mimi.h"
#include "rel.h"
#include "storage/block.h"
#include "access/offset.h"
#include "storage/bufmgr.h"
typedef struct IndexTupleData {
    int key;
    int value;
    int ctid;
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

typedef struct BTreeInsertData {
    IndexTuple itup;
    Size itemsz;
} BTreeInsertData;

typedef BTreeInsertData* BTreeInsert;


extern void btbuildempty(Relation rel);
extern bool btinsert(Relation rel, int key, int value);
extern bool btremove(Relation rel, int key);
extern bool btgettuple(Relation rel, int key, int* value);

#define P_NEW   INVALID_BLOCK
#define P_NONE                   0
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

#define BTreeTupleGetDownLink(itup) (itup->value)


// internal methods
extern IndexTuple _bt_make_tuple(int key, int value);
extern Buffer _bt_get_root(Relation rel);
extern Buffer _bt_get_buf(Relation rel, BlockNum blkno);
extern void _bt_init_page(Page page);
extern Buffer _bt_newroot(Relation rel, Buffer lbuf, Buffer rbuf);
// action
extern Buffer _bt_moveright(Relation rel, BTreeInsert key, Buffer buf);
extern Buffer _bt_relandgetbuf(Relation rel, Buffer obuf, BlockNum blkno);
extern bool _bt_addtup(Page page, Item item, Size itemsz, OffsetNumber newitemoffset);

// search
extern OffsetNumber _bt_binsrch(Relation rel, Page page, BTreeInsert key);
// insert
extern bool _bt_do_insert(Relation rel, IndexTuple itup);
extern BTreeInsert _bt_make_scankey(Relation rel, IndexTuple itup);
extern BTStack _bt_search(Relation rel, BTreeInsert itup_key, Buffer* bufp);
extern OffsetNumber _bt_findinsertloc(Relation rel, Buffer buffer, BTreeInsert key);
extern void _bt_insertonpg(Relation rel, Buffer buffer, OffsetNumber newitemoffset, BTreeInsert itup_key, BTStack stack);
extern Buffer _bt_split(Relation rel, IndexTuple itup, Buffer buf, OffsetNumber newitemoff);
extern void _bt_insert_parent(Relation rel, Buffer buf, Buffer rbuf, BTStack stack, bool is_root);
extern OffsetNumber _bt_find_split_offset(Buffer buf);
// compare
extern int _bt_compare(Relation rel, BTreeInsert key, Page page, OffsetNumber offset);

extern void _bt_freestack(BTStack stack);

#endif