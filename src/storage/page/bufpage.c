#include "storage/page.h"
#include "access/indextuple.h"
#include "util/mctx.h"
#include "access/offset.h"

void PageInit(Page page, Size pageSize, Size specialSize) {
    memset(page, 0, pageSize);

    PageHeader header = PageGetHeader(page);
    header->pd_lower = SizeOfPageHeaderData;
    header->pd_upper = BLKSZ - specialSize;
    header->pd_special = BLKSZ - specialSize;
    header->pd_flags = 0;

}


OffsetNumber PageAddItem(Page page, Item item, Size itemsz, OffsetNumber offsetNumber) {
    PageHeader header = PageGetHeader(page);
    // move item

    ItemId itemId = PageGetItemId(page, offsetNumber);

    OffsetNumber limit = OffsetNumberNext(PageGetMaxOffsetNumber(page));

    memmove(itemId + 1, itemId, (limit - offsetNumber) * sizeof(ItemIdData));

    header->pd_lower = header->pd_lower + sizeof(ItemIdData);

    // add index

    header->pd_upper = header->pd_upper - sizeof(IndexTupleData);

    // update item;
    itemId->lp_off = header->pd_upper;
    //itemId->lp_flags = IID_USE;
    itemId->lp_len = itemsz;

    memcpy((char*)page + header->pd_upper, item, itemsz);

    return offsetNumber;
}

void PageRemoveItem(Page page, OffsetNumber itemoffset) {
    PageHeader header = PageGetHeader(page);

    ItemId itemId = PageGetItemId(page, itemoffset);

    OffsetNumber limit = PageGetMaxOffsetNumber(page);

    memmove(itemId, itemId + 1, (limit - itemoffset) * sizeof(ItemIdData));

    header->pd_lower = header->pd_lower - sizeof(ItemIdData);
}

Page GetTempPage(Page page) {
    char* temp = (char*)palloc(BLKSZ);
    PageInit(temp, BLKSZ, 0);
    return temp;
}

Size PageGetFreeSpace(Page page) {
    PageHeader header = PageGetHeader(page);

    OffsetNumber space = header->pd_upper - header->pd_lower;
    if (space < sizeof(ItemIdData)) {
        return 0;
    }
    else {
        space -= sizeof(ItemIdData);
    }
    return space;
}

void PageRestoreTempPage(Page temp, Page origin) {
    int size = BLKSZ;
    memcpy((char*)origin, (char*)temp, size);

    pfree(temp);
}
