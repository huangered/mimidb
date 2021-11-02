#ifndef _btree_hpp_
#define _btree_hpp_

#include "mimi.hpp"
#include "access/amapi.hpp"
#include "access/genam.hpp"
#include "access/offset.hpp"
#include "access/rel.hpp"
#include "access/scankey.hpp"
#include "storage/block.hpp"
#include "storage/bufmgr.hpp"

struct IndexTupleData {
    int ht_id;      // record heap tuple id
    int tuple_size; // temporarily value;
    int key;
    // data part
};

typedef IndexTupleData* IndexTuple;

struct BTreeSpecialData {
    BlockNumber btsd_next;
    BlockNumber btsd_prev;
    union {
        uint16 level;
    } btsd;
    uint16 btsd_flags;
};

typedef BTreeSpecialData* BTreeSpecial;

/* btsd的bits定义*/
#define BTP_LEAF      (1 << 0)
#define BTP_ROOT      (1 << 1)
#define BTP_DELETED   (1 << 2) /* 已经在树中删除的页 */
#define BTP_META      (1 << 3) /* 元数据页 */
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

typedef BTStackData* BTStack;

class BTreeScanData {
public:
    IndexTuple itup;
    Size itemsz;
    bool nextkey;
    int keysz;
    ScanKey scankeys;

public:
    BTreeScanData(Size _keysz)
        : keysz(_keysz) {
        scankeys = new ScanKeyData[_keysz];
    }
    ~BTreeScanData() {
        delete[] scankeys;
    }
};

typedef BTreeScanData* BTreeScan;

struct BTreeSearchKeyData {
    int key;
};

typedef BTreeSearchKeyData* BTreeSearchKey;

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

#define BTreeTupleGetDownLink(itup) (itup->ht_id)

// 函数原型

class BtreeIndex : public IndexAm {
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
    bool _bt_do_insert(Relation rel, IndexTuple itup, IndexUniqueCheck checkUnique, Relation heapRel);
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
    BtreeIndex();
    virtual void BuildEmpty(Relation rel);
    virtual bool Insert(Relation rel, int nkey, int ht_id);
    virtual bool Remove(Relation rel, int nkey);
    virtual IndexScanDesc BeginScan(Relation nrel, int nkeys, ScanKey key);
    virtual bool GetNext(IndexScanDesc scan, ScanDirection dir);
    virtual void EndScan(Relation rel, int nkeys);
    virtual void Vacuum(Relation rel);

    void debug(Relation rel);
};

extern IndexAm* BtreeRoute();

#endif
