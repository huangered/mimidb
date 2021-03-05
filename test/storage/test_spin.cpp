//#include "../g.hpp"
//
//
//
//#include "storage/spin.hpp"
//
//
//
//// test the basic usage in buff mgr.
//TEST(Storage, spin)
//{
//    slock_t a;
//    SpinLockInit(&a);
//    EXPECT_EQ(a, 0);
//    SpinLockAcquire(&a);
//    EXPECT_EQ(a, 1);
//    SpinLockRelease(&a);
//    EXPECT_EQ(a, 0);
//}