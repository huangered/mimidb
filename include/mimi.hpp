#ifndef _mimi_hpp_
#define _mimi_hpp_

#include "c.hpp"

typedef unsigned long long Oid;

#define InvalidOid				((Oid)0)

inline bool OidIsValid(Oid objectId) {
	return objectId == InvalidOid;
}

typedef uintptr_t Datum;

#define OidGetDatum(X)      static_cast<Datum>(X)
#define DatumGetOid(X)      static_cast<Oid>(X)

#define IntGetDatum(X)      static_cast<Datum>(X)
#define DatumGetInt(X)      static_cast<int>(X)

#define PointerGetDatum(X)	reinterpret_cast<Datum>(X)
#define DatumGetPointer(X)	reinterpret_cast<void*>(X)

#define NAME_LIMIT  64

#define TYPEALIGN(ALIGNVAL,LEN)  \
	(((uintptr_t) (LEN) + ((ALIGNVAL) - 1)) & ~((uintptr_t) ((ALIGNVAL) - 1)))

#define FLEX_ARRAY_SIZE

#define Assert(X) assert(X)

#endif