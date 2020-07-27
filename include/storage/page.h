#ifndef _PAGE_H_
#define _PAGE_H_

#include "mimi.h"

#define BLKSZ   8012

typedef char* Page;

typedef struct PageHeaderData {

    uint16 pd_checksum;
    uint16 pd_flags;

    int pd_lower;
    int pd_upper;
    int pd_special;

} PageHeaderData;

typedef PageHeaderData* PageHeader;

#define PageIsNew(page) (((PageHeader)(page))->pd_upper == 0)


void PageInit(Page page, Size pageSize);

#endif // !_PAGE_H_
