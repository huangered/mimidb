#include "catalog/catalog.hpp"

static Oid fakeOid = 100000;

Oid
GetNewOid() {
	return fakeOid++;
}