#ifndef _page_hpp_
#define _page_hpp_

#include "mimi.h"
#include "storage/itemid.h"
#include "access/offset.h"

#define BLKSZ 8192

typedef char* Page;

/*
 * 页表中的偏移，大小限制在 2^15 内。
 */
typedef uint16 LocationIndex;

typedef struct PageHeaderData {
    long pd_lsn; /* lsn 号 */

    uint16 pd_checksum;
    uint16 pd_flags;

    LocationIndex pd_lower;   /* 空闲空间开始 */
    LocationIndex pd_upper;   /* 空闲空间结束 */
    LocationIndex pd_special; /* 特殊空间开始 */
    uint16 pd_pagesize_version;
    ItemIdData pd_linp[];
} PageHeaderData;

typedef PageHeaderData* PageHeader;

#define PD_PAGE_FREE_LINES 0x01
#define PD_PAGE_FULL       0x02
#define PD_ALL_VISIBLE     0x04
#define PD_VALID_FLAG_BITS 0x07

#define PD_PAGE_LAYOUT_VERSION   1
#define PD_DATA_CHECKSUM_VERSION 1

/* page 辅助宏 */
#define PageIsValid(page) (page != NULL)

/*
 * line point 不统计在内
 */
#define SizeOfPageHeaderData (offsetof(PageHeaderData, pd_linp))

#define PageGetHeader(page)  ((PageHeader)page)
#define PageGetContent(page) ((char*)(page + SizeOfPageHeaderData))
#define PageGetSpecial(page) (BTreeSpecial)(page + PageGetHeader(page)->pd_special)

inline bool
PageIsNew(Page page) {
    return ((PageHeader)(page))->pd_upper == 0;
}

inline size_t
PageGetMaxOffsetNumber(Page page) {
    OffsetNumber lower = PageGetHeader(page)->pd_lower;
    return lower <= SizeOfPageHeaderData ? 0 : (lower - SizeOfPageHeaderData) / sizeof(ItemIdData);
}

inline ItemId
PageGetItemId(Page page, OffsetNumber offsetnum) {
    return &PageGetHeader(page)->pd_linp[offsetnum - 1];
}

inline Item
PageGetItem(Page page, ItemId itemId) {
    return (((char*)(page)) + itemId->lp_off);
}

/* 公用函数声明 */
void PageInit(Page page, Size pageSize, Size specialSize);
OffsetNumber PageAddItem(Page page, Item item, Size size, OffsetNumber offsetNumber, bool is_heap);
OffsetNumber PageAddItemExtend(Page page, Item item, Size size, OffsetNumber offsetNumber, int flags);
void PageRemoveItem(Page page, OffsetNumber offsetNum);
Page GetTempPage(Page page);
Size PageGetFreeSpace(Page page);
void PageRestoreTempPage(Page temp, Page origin);

#endif
