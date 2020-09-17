#include "../g.h"

_EXTERN_C
#include "storage/fd.h"
#include "storage/page.h"
_END_EXTERN_C

// test the basic usage in buff mgr.
TEST(fd, basic)
{
    file_init("peter.bak");
    fd* one1 = file_open("peter.bak");
    char* buf = (char*)malloc(BLKSZ);
    memset(buf, 'c', BLKSZ);
    file_write(one1, 0, buf);
    char* other = (char*)malloc(BLKSZ);
    memset(other, 0, BLKSZ);
    file_read(one1, 0, other);
    int size = file_size(one1);
    EXPECT_EQ(size, BLKSZ);
    file_close(one1);
}