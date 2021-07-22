#include "../g.hpp"
#include "storage/fd.hpp"

TEST(fd, OpFile)
{
    const char* buf = "tmp_file.txt";
    int fd = PathNameOpenFile(buf);
    EXPECT_GT(fd, 0);

    char* buf2 = "abcdefghijklmnopqrstuvwxyz";

    FileSeek(fd, 0, SEEK_END);

    int num = FileWrite(fd, buf2, 26);

    EXPECT_GT(num, 0);

    num = FileSync(fd);

    EXPECT_EQ(num, 0);

    FileSeek(fd, 0, SEEK_SET);

    char* buf3 = new char[256];

    num = FileRead(fd, buf3, 26);

    EXPECT_GT(num, 0);

    delete[] buf3;

    FileClose(fd);
}