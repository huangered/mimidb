#ifndef _g_h_
#define _g_h_

#include <gtest/gtest.h>

#ifdef __linux__

#define _EXTERN_C     extern "C" {
#define _END_EXTERN_C }

#endif

#endif // !_g_h_
