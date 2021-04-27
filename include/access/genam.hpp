/*
 * general index api function
 */
#ifndef _genam_hpp_
#define _genam_hpp_

#include "access/rel.hpp"
#include "access/scankey.hpp"
#include "access/scan.hpp"

SysTableScanDesc systable_beginscan(Relation sysrelation, int nkeys, ScanKey key);
HeapTuple systable_getnext(SysTableScanDesc scan);
void systable_endscan(SysTableScanDesc scan);

#endif // !_GENAM_H_
