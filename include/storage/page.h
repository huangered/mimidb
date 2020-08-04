#ifndef _PAGE_H_
#define _PAGE_H_

#include "mimi.h"
#include "storage/itemid.h"

#define BLKSZ   8012

typedef char* Page;

typedef struct PageHeaderData {

    uint16 pd_checksum;
    uint16 pd_flags;

    int pd_lower;
    int pd_upper;
    int pd_special;

    ItemIdData pd_linp[1];
} PageHeaderData;

typedef PageHeaderData* PageHeader;


#define PageIsNew(page)                 (((PageHeader)(page))->pd_upper == 0)
#define SizeOfPageHeaderData            (offsetof(PageHeaderData, pd_linp))
#define PageGetContent(page)            ((char*)(page + SizeOfPageHeaderData))
#define PageGetMaxOffsetNumber(page) \
    (((PageHeader) (page))->pd_lower <= SizeOfPageHeaderData ? 0 : \
    ((((PageHeader) (page))->pd_lower - SizeOfPageHeaderData) / sizeof(ItemIdData)))
#define PageGetItemId(page, offsetnum)  ((ItemId)(&(((PageHeader)(page))->pd_linp[offsetnum - 1])))
#define PageGetItem(page, itemId)       (((char*)(page)) + itemId->lp_off)

void PageInit(Page page, Size pageSize);

#endif // !_PAGE_H_
