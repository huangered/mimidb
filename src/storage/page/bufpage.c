#include "storage/page.h"

void PageInit(Page page, Size pageSize) {
    memset(page, 0, pageSize);
}