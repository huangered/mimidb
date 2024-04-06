#ifndef _btree_h_
#define _btree_h_

#include "mimi.h"
#include "access/amapi.h"
#include "access/genam.h"
#include "access/indextuple.h"
#include "access/offset.h"
#include "access/rel.h"
#include "access/relscan.h"
#include "access/scankey.h"
#include "storage/block.h"
#include "storage/bufmgr.h"

struct BTreeSpecialData {
    BlockNumber btsd_next;
    BlockNumber btsd_prev;
    union {
        uint16 level;
    } btsd;
    uint16 btsd_flags;
};

typedef struct BTreeSpecialData* BTreeSpecial;

/* btsd的bits定义*/
#define BTP_LEAF      (1 << 0)
#define BTP_ROOT      (1 << 1)
#define BTP_DELETED   (1 << 2) /* 已经在树中删除的页 */
#define BTP_META      (1 << 3) /* 元数据页 */
#define BTP_OTHER     (1 << 4)
#define BTP_SPLIT_END (1 << 5) /* 分割组里最右页 */

struct BTreeMetaData {
    uint32 btm_magic;
    uint32 btm_version;
    BlockNumber btm_root; /* 当前根页位置 */
    uint32 btm_level;     /* 根页的level*/
    BlockNumber fastroot;
};

#define BTREE_METAPAGE 0 /* 默认第一页是 meta */
#define BTREE_MAGIC    0x1234
#define BTREE_VERSION  1

struct BTStackData {
    BlockNumber blkno;
    OffsetNumber offset;
    struct BTStackData* parent;
};

typedef struct BTStackData* BTStack;

struct BTreeScanData {
    IndexTuple itup;
    Size itemsz;
    bool nextkey;
    int keysz;
    ScanKey scankeys;
};

typedef struct BTreeScanData* BTreeScan;

struct BTreeSearchKeyData {
    int key;
};

typedef struct BTreeSearchKeyData* BTreeSearchKey;

#define P_NONE 0

/*
 * 测试 page 位置的宏
 */
#define P_LEFTMOST(special)  ((special)->btsd_prev == P_NONE)
#define P_RIGHTMOST(special) ((special)->btsd_next == P_NONE)
#define P_ISLEAF(special)    ((special)->btsd_flags & BTP_LEAF)
#define P_ISROOT(special)    ((special)->btsd_flags & BTP_ROOT)
#define P_ISDELETED(special) ((special)->btsd_flags & BTP_DELETED)

#define IID_USE (1 << 0)
#define IID_DEL (1 << 1)

/*
 * lehman and Yao's 算法
 */
#define P_HIKEY                 ((OffsetNumber)1)
#define P_FIRSTKEY              ((OffsetNumber)2)
#define P_FIRSTDATAKEY(special) (P_RIGHTMOST(special) ? P_HIKEY : P_FIRSTKEY)

#define BTreeTupleGetDownLink(itup) (itup->t_tid.ip_blkno)

// 函数原型 extern entry points for btree, in btree.c
extern IndexBuildResult* btbuild(Relation heap, Relation index);
extern bool btinsert(Relation rel, int key, int ht_id);
extern bool btremove(Relation rel, int key);
extern bool btgetnext(IndexScanDesc scan, enum ScanDirection dir);
extern IndexScanDesc btbeginscan(Relation nrel, int nkeys, ScanKey key);
extern void btendscan(Relation rel, int nkeys);

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
bool _bt_do_insert(Relation rel, IndexTuple itup, enum IndexUniqueCheck checkUnique, Relation heapRel);
BTStack _bt_search(Relation rel, BTreeScan itup_key, Buffer* bufp);

bool _bt_addtup(Page page, Item item, Size itemsz, OffsetNumber newitemoffset);
void _bt_insertonpg(Relation rel, Buffer buffer, OffsetNumber newitemoffset, BTreeScan itup_key, BTStack stack);
void _bt_insert_parent(Relation rel, Buffer lbuf, Buffer rbuf, BTStack stack, bool is_root);

struct BTreeMetaData* _bt_getmeta(Relation rel, Buffer metabuf);
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

#endif
