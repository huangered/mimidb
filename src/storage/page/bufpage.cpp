#include "access/indextuple.hpp"
#include "access/offset.hpp"
#include "storage/page.hpp"
#include "util/mctx.hpp"

/*
init the raw page
1. set the page header
2. set the page version
*/
void 
PageInit(Page page, Size pageSize, Size specialSize) {
    memset(page, 0, pageSize);

    PageHeader header = PageGetHeader(page);
    header->pd_lower = SizeOfPageHeaderData;
    header->pd_upper = BLKSZ - specialSize;
    header->pd_special = BLKSZ - specialSize;
    header->pd_flags = 0;

}

// 插入item到页中
// 返回插入的offset
OffsetNumber 
PageAddItem(Page page, Item item, Size itemsz, OffsetNumber offsetNumber) {
    PageHeader header = PageGetHeader(page);
    OffsetNumber limit;
    ItemId itemId;
    int lower;
    int upper;
    bool needshuffle{ false };

    // 设定offset最后位置
    limit = OffsetNumberNext(PageGetMaxOffsetNumber(page));

    // 如果传入的offset是无效的，找个新位置
    if (OffsetIsValid(offsetNumber)) {
        // 查找没有在使用的item
    }
    else {
        offsetNumber = limit;
    }

    if (offsetNumber < limit) {
        needshuffle = true;
    }

    // 计算新的lower和upper位置
    if (offsetNumber == limit || needshuffle) {
        lower = header->pd_lower + sizeof(ItemIdData);
    }
    else {
        lower = header->pd_lower;
    }

    upper = header->pd_upper - itemsz;

    // move item
    itemId = PageGetItemId(page, offsetNumber);   
    
    if (needshuffle) {
        memmove(itemId + 1, itemId, (limit - offsetNumber) * sizeof(ItemIdData));
    }    

    // update item;
    itemId->lp_off = upper;
    // itemId->lp_flags = IID_USE;
    itemId->lp_len = itemsz;

    memcpy((char*)page + upper, item, itemsz);

    header->pd_lower = lower;
    header->pd_upper = upper;

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
    char* temp = new char[BLKSZ];
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

    delete[] temp;
}
