#ifndef _PAGE_H_
#define _PAGE_H_

#include "mimi.hpp"
#include "storage/itemid.hpp"
#include "access/offset.hpp"

#define BLKSZ   8192

typedef char* Page;

class PageBuf {
public:
    Page page;
};

typedef struct PageHeaderData {

    uint16 pd_checksum;
    uint16 pd_flags;

    OffsetNumber pd_lower;
    OffsetNumber pd_upper;
    OffsetNumber pd_special;

    ItemIdData pd_linp[1];
} PageHeaderData;

typedef PageHeaderData* PageHeader;


#define PageIsNew(page)                 (((PageHeader)(page))->pd_upper == 0)
#define SizeOfPageHeaderData            (offsetof(PageHeaderData, pd_linp))
#define PageGetHeader(page)             ((PageHeader)page)
#define PageGetContent(page)            ((char*)(page + SizeOfPageHeaderData ))
#define PageGetSpecial(page)            ((char*)(page + PageGetHeader(page)->pd_special ))
#define PageGetMaxOffsetNumber(page) \
    (((PageHeader) (page))->pd_lower <= SizeOfPageHeaderData ? 0 : \
    ((((PageHeader) (page))->pd_lower - SizeOfPageHeaderData) / sizeof(ItemIdData)))
#define PageGetItemId(page, offsetnum)  ((ItemId)(&(((PageHeader)(page))->pd_linp[offsetnum - 1])))
#define PageGetItem(page, itemId)       (((char*)(page)) + itemId->lp_off)

void PageInit(Page page, Size pageSize, Size specialSize);

OffsetNumber PageAddItem(Page page, Item item, Size size, OffsetNumber offsetNumber);
void PageRemoveItem(Page page, OffsetNumber offsetNum);

Page GetTempPage(Page page);
Size PageGetFreeSpace(Page page);
void PageRestoreTempPage(Page temp, Page origin);
#endif // !_PAGE_H_
