#include "catalog/catalog.h"

static Oid fakeOid = 100000;

Oid
GetNewOid() {
	return fakeOid++;
}