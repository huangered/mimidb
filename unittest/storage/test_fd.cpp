#include "../g.hpp"

extern "C" {
#include "storage/fd.h"
}

TEST(fd, basic) {
    const char* buf = "tmp_file.txt";
    int fd          = PathNameOpenFile(buf);
    int num{ 0 };
    char* buf3{ nullptr };
    EXPECT_GT(fd, 0);

    const char* buf2 = "abcdefghijklmnopqrstuvwxyz";

    FileSeek(fd, 0, SEEK_END);

    num = FileWrite(fd, buf2, 26);

    EXPECT_GT(num, 0);

    num = FileSync(fd);

    EXPECT_EQ(num, 0);

    FileSeek(fd, 0, SEEK_SET);

    buf3 = new char[256];

    num = FileRead(fd, buf3, 26);

    EXPECT_GT(num, 0);

    delete[] buf3;

    FileClose(fd);
}
