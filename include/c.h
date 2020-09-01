#ifndef _C_H_
#define _C_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <memory.h>

typedef size_t Size;
typedef unsigned short uint16;
typedef unsigned int uint32;

/*
 * Max
 *		Return the maximum of two numbers.
 */
#define Max(x, y)		((x) > (y) ? (x) : (y))

#endif // !_C_H_
