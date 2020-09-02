#include "../g.h"

_EXTERN_C

#include "storage/spin.h"

_END_EXTERN_C

// test the basic usage in buff mgr.
TEST(spin, spin)
{
    slock_t a;
    SpinLockInit(&a);
    EXPECT_EQ(a, 0);
    SpinLockAcquire(&a);
    EXPECT_EQ(a, 1);
    SpinLockRelease(&a);
    EXPECT_EQ(a, 0);
}