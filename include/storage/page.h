#ifndef _PAGE_H_
#define _PAGE_H_

#include "mimi.h"

#define BLKSZ   8012

typedef char* Page;

typedef struct PageHeaderData {

    uint16 pd_checksum;
    uint16 pd_flags;

} PageHeaderData;

typedef PageHeaderData* PageHeader;

void PageInit(Page page);

#endif // !_PAGE_H_
