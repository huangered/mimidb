#include "access/indextuple.h"
#include "access/offset.h"
#include "storage/page.h"

/*
init the raw page
1. set the page header
2. set the page version
*/
void
PageInit(Page page, Size pageSize, Size specialSize) {
    memset(page, 0, pageSize);

    PageHeader header  = PageGetHeader(page);
    header->pd_lower   = SizeOfPageHeaderData;
    header->pd_upper   = BLKSZ - specialSize;
    header->pd_special = BLKSZ - specialSize;
    header->pd_flags   = 0;
}

OffsetNumber
PageAddItem(Page page, Item item, Size itemsz, OffsetNumber offsetNumber, bool is_heap) {
    return PageAddItemExtend(page, item, itemsz, offsetNumber, 0);
}

OffsetNumber
PageAddItemExtend(Page page, Item item, Size itemsz, OffsetNumber offsetNumber, int flags) {
    PageHeader header = PageGetHeader(page);
    int lower;
    int upper;
    ItemId itemId;
    OffsetNumber limit;
    bool needShuffle = false;

    limit = OffsetNumberNext(PageGetMaxOffsetNumber(page));

    // if the offset == invalid, find a new one
    if (offsetNumber != InvalidOffsetNumber) {
        if (offsetNumber < limit)
            needShuffle = true;
    } else {
        offsetNumber = PageGetMaxOffsetNumber(page);
        offsetNumber = OffsetNumberNext(offsetNumber);
    }

    if (offsetNumber == limit || needShuffle) {
        lower = header->pd_lower + sizeof(struct ItemIdData);
    } else {
        lower = header->pd_lower;
    }

    upper = (int)header->pd_upper - (int)itemsz;

    if (lower > upper) {
        return InvalidOffsetNumber;
    }

    itemId = PageGetItemId(page, offsetNumber);

    if (needShuffle) {
        memmove(itemId + 1, itemId, (limit - offsetNumber) * sizeof(struct ItemIdData));
    }

    // set item pointer
    itemId->lp_off = upper;
    itemId->lp_len = itemsz;

    // copy data
    memcpy((char*)page + upper, item, itemsz);

    // adjust page header
    header->pd_lower = (LocationIndex)lower;
    header->pd_upper = (LocationIndex)upper;

    return offsetNumber;
}

void
PageRemoveItem(Page page, OffsetNumber itemoffset) {
    PageHeader header = PageGetHeader(page);

    ItemId itemId = PageGetItemId(page, itemoffset);

    OffsetNumber limit = PageGetMaxOffsetNumber(page);

    memmove(itemId, itemId + 1, (limit - itemoffset) * sizeof(struct ItemIdData));

    header->pd_lower = header->pd_lower - sizeof(struct ItemIdData);
}

Page
GetTempPage(Page page) {
    char* temp = palloc(BLKSZ);
    return temp;
}

Size
PageGetFreeSpace(Page page) {
    PageHeader header = PageGetHeader(page);

    OffsetNumber space = header->pd_upper - header->pd_lower;
    if (space < sizeof(struct ItemIdData)) {
        return 0;
    } else {
        space -= sizeof(struct ItemIdData);
    }
    return space;
}

void
PageRestoreTempPage(Page temp, Page origin) {
    int size = BLKSZ;
    memcpy((char*)origin, (char*)temp, size);

    palloc(temp);
}
