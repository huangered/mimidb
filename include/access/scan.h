#ifndef _SCAN_H_
#define _SCAN_H_

#include "access/relation.h"
#include "access/scankey.h"

typedef struct TableScanDescData {
	Relation rs_rel;
	int rs_nkeys;
	ScanKey rs_key;
} TableScanDescData;

typedef TableScanDescData* TableScanDesc;

#endif