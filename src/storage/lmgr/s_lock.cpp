#include "storage/spin.hpp"

int
s_lock(volatile slock_t* lock, const char* file, int line) {
    while (TAS_SPIN(lock)) {
    }
    return 0;
}