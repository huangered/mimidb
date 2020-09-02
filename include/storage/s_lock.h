#ifndef _s_lock_h_
#define _s_lock_h_

    #ifdef _MSC_VER
    #include <Windows.h>

    typedef long slock_t;

    #define TAS(lock) (InterlockedCompareExchange(lock, 1, 0))
    #define TAS_SPIN(lock)	TAS(lock)

    #include <intrin.h>
    #pragma intrinsic(_ReadWriteBarrier)

    #define S_UNLOCK(lock)	\
        do { _ReadWriteBarrier(); (*(lock)) = 0; } while (0)

    #define S_LOCK(lock) \
        (TAS(lock) ? s_lock((lock), __FILE__, __LINE__) : 0)

    #define S_INIT_LOCK(lock)	S_UNLOCK(lock)

    #endif

    extern int s_lock(volatile slock_t * lock, const char* file, int line);

#endif