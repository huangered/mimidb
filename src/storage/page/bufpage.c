#include "storage/page.h"

void PageInit(Page page) {
    memset(page, 0, BLKSZ);
}