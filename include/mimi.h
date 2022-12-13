#ifndef _MIMI_H_
#define _MIMI_H_

#include "c.h"
#include "util/palloc.h"

typedef unsigned long long Oid;

#define InvalidOid           ((Oid)0)
#define OidIsValid(objectId) ((bool)(objectId == InvalidOid))

typedef uintptr_t Datum;

#define IntGetDatum(X) ((Datum)(X))
#define DatumGetInt(X) ((int)(X))

#define PointerGetDatum(X) ((Datum)(X))
#define DatumGetPointer(X) ((void*)(X))

#define NAME_LIMIT 64

#define TYPEALIGN(ALIGNVAL, LEN) (((uintptr_t)(LEN) + ((ALIGNVAL)-1)) & ~((uintptr_t)((ALIGNVAL)-1)))

#define FLEX_ARRAY_SIZE

#endif