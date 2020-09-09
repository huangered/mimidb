#ifndef _MIMI_H_
#define _MIMI_H_

#include "c.h"

typedef unsigned long long Oid;

typedef uintptr_t Datum;

#define IntGetDatum(X)      ((Datum)(X))
#define DatumGetInt(X)      ((int)(X))

#define NAME_LIMIT  64

#endif