//#include "../g.hpp"
//
//#include "access/btree.hpp"
//#include "storage/bufmgr.hpp"
//#include "storage/freespace.hpp"
//#include "storage/smgr.hpp"
//#include "util/mctx.hpp"
//#include "util/sysdbg.hpp"
//
//// test the basic usage in buff mgr.
//TEST(btree, incr_insert)
//{
//    std::shared_ptr<BufferMgr> mgr = std::make_shared<BufferMgr>();
//
//    freespace fspace{};
//    Relation rel = new RelationData;
//    rel->rnode = 10000;
//    rel->oid = 1;
//    rel->root_blkno = P_NONE;
//    rel->index_am = new BtreeIndex(mgr);
//    rel->index_am->buildempty(rel);
//    rel->rd_smgr = new SMgrRelationData;
//    rel->rd_smgr->smgr_fsm_nblocks = 0;
//
//    fspace.RecordPageWithFreeSpace(rel, 0, BLKSZ);
//    fspace.FreeSpaceMapVacuumRange(rel, 0, 1);
//
//    for (int i = 0; i < 10; i++) {
//        printf("%d\r\n", i);
//        bool result = rel->index_am->insert(rel, i, i);
//        EXPECT_TRUE(result);
//    }
//
//    delete rel->rd_smgr;
//    delete rel;
//}

//TEST(btree, decr_insert)
//{
//    MemoryContextInit();
//    //BufferInit();
//
//    Relation rel = (Relation)palloc(sizeof(RelationData));
//    rel->rnode = 10001;
//    rel->root_blkno = P_NONE;
//    rel->index_am = buildRoute();
//    rel->index_am->ambuildempty(rel);
//
//    rel->rd_smgr = (SmgrRelation)palloc(sizeof(SMgrRelationData));
//    rel->rd_smgr->smgr_fsm_nblocks = 0;
//
//    freespace{}.RecordPageWithFreeSpace(rel, 0, BLKSZ);
//    freespace{}.FreeSpaceMapVacuumRange(rel, 0, 1);
//
//
//    for (int i = 0; i < 10; i++) {
//        //printf("%d\r\n", i);
//        bool result = rel->index_am->aminsert(rel, i, i);
//        EXPECT_TRUE(result);
//    }
//
//    //debug_rel(rel);
// 
//    for (int i = 0; i < 10; i++) {
//        IndexScanDesc scan = (IndexScanDesc)palloc(sizeof(IndexScanDescData));
//        scan->index_rel = rel;
//        scan->key = i;
//        scan->block = INVALID_BLOCK;
//        bool result = rel->index_am->amgettuple(scan);
//        EXPECT_TRUE(result);
//        EXPECT_EQ(scan->value, i);
//        result = rel->index_am->amgettuple(scan);
//        EXPECT_FALSE(result);
//        pfree(scan);
//    }
//    pfree(rel->rd_smgr);
//    pfree(rel);
//}