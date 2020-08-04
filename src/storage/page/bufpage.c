#include "storage/page.h"

void PageInit(Page page, Size pageSize, Size specialSize) {
    memset(page, 0, pageSize);

    PageHeader header = PageGetHeader(page);
    header->pd_lower = SizeOfPageHeaderData;
    header->pd_upper = BLKSZ - specialSize;
    header->pd_special = BLKSZ - specialSize;
    header->pd_flags = 0;

}