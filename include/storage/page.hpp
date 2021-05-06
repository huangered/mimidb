#ifndef _page_hpp_
#define _page_hpp_

#include "mimi.hpp"
#include "storage/itemid.hpp"
#include "access/offset.hpp"

// page 默认大小 8k
const int BLKSZ{ 8192 };

typedef char* Page;

typedef struct PageHeaderData {

    uint16 pd_checksum;
    uint16 pd_flags;

    OffsetNumber pd_lower;
    OffsetNumber pd_upper;
    OffsetNumber pd_special;

    ItemIdData pd_linp[];
} PageHeaderData;

typedef PageHeaderData* PageHeader;

#define SizeOfPageHeaderData            (offsetof(PageHeaderData, pd_linp))
#define PageGetHeader(page)             ((PageHeader)page)
#define PageGetContent(page)            ((char*)(page + SizeOfPageHeaderData ))
#define PageGetSpecial(page)            (BTreeSpecial)(page + PageGetHeader(page)->pd_special )

inline bool PageIsNew(Page page) {
    return ((PageHeader)(page))->pd_upper == 0;
}

inline size_t PageGetMaxOffsetNumber(Page page) {
    OffsetNumber lower = PageGetHeader(page)->pd_lower;
    return lower <= SizeOfPageHeaderData ? 0 : (lower - SizeOfPageHeaderData) / sizeof(ItemIdData);
}

inline ItemId PageGetItemId(Page page, OffsetNumber offsetnum) {
    return &PageGetHeader(page)->pd_linp[offsetnum - 1];
}

inline Item PageGetItem(Page page, ItemId itemId) {
    return (((char*)(page)) + itemId->lp_off);
}

void PageInit(Page page, Size pageSize, Size specialSize);

OffsetNumber PageAddItem(Page page, Item item, Size size, OffsetNumber offsetNumber);
void PageRemoveItem(Page page, OffsetNumber offsetNum);

Page GetTempPage(Page page);
Size PageGetFreeSpace(Page page);
void PageRestoreTempPage(Page temp, Page origin);

#endif 
