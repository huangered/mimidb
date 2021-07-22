#include "../g.hpp"
#include "storage/fd.hpp"

TEST(fd, OpenFile)
{
    char* buf = "C:\\work\\mimidb\\sql.rule";

    int fd = PathNameOpenFile(buf);



    EXPECT_GT(fd, 0);

}