/*
 * general index api function
 */
#ifndef _genam_hpp_
#define _genam_hpp_

#include "access/rel.hpp"
#include "access/scankey.hpp"
#include "access/scan.hpp"

enum IndexUniqueCheck {
    UNIQUE_CHECK_NO,  /* 不做 unique 检查 */
    UNIQUE_CHECK_YES, /* 插入时检查 unique */
    UNIQUE_CHECK_EXISTING,
};

SysTableScan systable_beginscan(Relation sysrelation, int nkeys, ScanKey key);
HeapTuple systable_getnext(SysTableScan scan);
void systable_endscan(SysTableScan scan);

#endif // !_GENAM_H_
