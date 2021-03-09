#include "../g.hpp"
#include "storage/disk.hpp"
#include "storage/page.hpp"

TEST(disk, basic)
{
    char* buf = new char[BLKSZ];
    memset(buf, 0, BLKSZ);
    std::filesystem::path path{ "a.txt" };
    disk df{ path };
    df.create();
    bool result = df.open();
    EXPECT_TRUE(result);
    int num = df.nblock();
    EXPECT_EQ(num, 0);
    df.write(buf, 0);
    num = df.nblock();
    EXPECT_EQ(num, 1);
    df.close();
    delete[] buf;
}