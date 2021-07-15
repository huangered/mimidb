/*
自旋锁实现，只支持一下编译器
1. gcc, intel
2. mvc
*/
#ifndef _s_lock_h_
#define _s_lock_h_
#if defined(__GNUC__) || defined(__INTEL_COMPILER)
typedef unsigned char slock_t;

#define TAS(lock) tas(lock)

static __inline__ int
tas(volatile slock_t* lock) {
    slock_t _res = 1;

    /*
     * Use a non-locking test before asserting the bus lock.  Note that the
     * extra test appears to be a small loss on some x86 platforms and a small
     * win on others; it's by no means clear that we should keep it.
     *
     * When this was last tested, we didn't have separate TAS() and TAS_SPIN()
     * macros.  Nowadays it probably would be better to do a non-locking test
     * in TAS_SPIN() but not in TAS(), like on x86_64, but no-one's done the
     * testing to verify that.  Without some empirical evidence, better to
     * leave it alone.
     */
    //		__asm__ __volatile__(
    //			"	cmpb	$0,%1	\n"
    //			"	jne		1f		\n"
    //			"	lock			\n"
    //			"	xchgb	%0,%1	\n"
    //			"1: \n"
    //			//:		"+q"(_res), "+m"(*lock)
    //			:		/* no inputs */
    //			: "memory", "cc");
    return (int)_res;
}
#define TAS_SPIN(lock) TAS(lock)

#define S_UNLOCK(lock)                                                                                                 \
    do {                                                                                                               \
        __asm__ __volatile__("" : : : "memory");                                                                       \
        *(lock) = 0;                                                                                                   \
    } while (0)

#endif

#ifdef _MSC_VER
#include <Windows.h>

typedef long slock_t;

#define TAS(lock) (InterlockedCompareExchange(lock, 1, 0))
#define TAS_SPIN(lock) TAS(lock)

#include <intrin.h>
#pragma intrinsic(_ReadWriteBarrier)

#define S_UNLOCK(lock)                                                                                                 \
    do {                                                                                                               \
        _ReadWriteBarrier();                                                                                           \
        (*(lock)) = 0;                                                                                                 \
    } while (0)

#endif

#define S_LOCK(lock) (TAS(lock) ? s_lock((lock), __FILE__, __LINE__) : 0)

#define S_INIT_LOCK(lock) S_UNLOCK(lock)

extern int s_lock(volatile slock_t* lock, const char* file, int line);

#endif
