/*
#include "../g.hpp"
#include "storage/smgr.hpp"

TEST(disk, basic)
{
    char* buf = new char[BLKSZ];
    memset(buf, 96, BLKSZ);

    RelFileNode rnode = { 500,500 };

    SMgrRelation reln = smgr->Open(rnode);

    BlockNumber bn = smgr->Nblocks(reln, MAIN_FORKNUM);
    EXPECT_EQ(bn, 0);
    smgr->Write(reln, MAIN_FORKNUM, 0, buf);

    bn = smgr->Nblocks(reln, MAIN_FORKNUM);
    EXPECT_EQ(bn, 1);
    smgr->Close(reln);

}
 */