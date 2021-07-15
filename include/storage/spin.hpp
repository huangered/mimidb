/*
自旋锁相关代码
*/
#ifndef _spin_h_
#define _spin_h_

#include "storage/s_lock.hpp"

#define SpinLockInit(lock) S_INIT_LOCK(lock)

#define SpinLockAcquire(lock) S_LOCK(lock)

#define SpinLockRelease(lock) S_UNLOCK(lock)

#define SpinLockFree(lock) S_UNLOCK(lock)

#endif