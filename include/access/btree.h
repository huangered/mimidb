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

#define BTP_ROOT    0
#define BTP_LEAF    1

#define P_ISLEAF(special)   true

#define BTreeTupleGetDownLink(itup) (itup->value)


// internal methods
IndexTuple _bt_make_tuple(int key, int value);
Buffer _bt_get_root(Relation rel);
Buffer _bt_get_buf(Relation rel, BlockNum blkno);
void _bt_init_page(Page page);
// action
Buffer _bt_moveright(Relation rel, IndexTuple itup, Buffer buf);
Buffer _bt_relandgetbuf(Relation rel, Buffer obuf, BlockNum blkno);

// search
OffsetNumber _bt_binsrch(Relation rel, Page page, IndexTuple itup);
// insert
bool _bt_do_insert(Relation rel, IndexTuple itup);
BTreeInsert _bt_make_scankey(Relation rel, IndexTuple itup);
BTStack _bt_search(Relation rel, BTreeInsert itup_key, Buffer* bufp);
OffsetNumber _bt_findinsertloc(Relation rel, Buffer buffer, BTreeInsert key);
void _bt_insertonpg(Relation rel, Buffer buffer, OffsetNumber newitemoffset, BTreeInsert itup_key, BTStack stack);

void _bt_freestack(BTStack stack);
#endif