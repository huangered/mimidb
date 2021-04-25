/*
 * general index api function
 */
#ifndef _genam_hpp_
#define _genam_hpp_

#include "access/rel.hpp"
#include "access/scankey.hpp"
#include "access/scan.hpp"

SysTableScan systable_beginscan(Relation sysrelation, int nkeys, ScanKey key);
HeapTuple systable_getnext(SysTableScan scan);
void systable_endscan(SysTableScan scan);

#endif // !_GENAM_H_
