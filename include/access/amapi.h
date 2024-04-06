/*
 * define all index access methods.
 */
#ifndef _amapi_h_
#define _amapi_h_

#include "mimi.h"
#include "access/genam.h"

typedef IndexBuildResult* (*ambuild_function)(Relation heapRealtion, Relation indexRelation);
typedef bool (*aminsert_function)(Relation rel, int nkey, int ht_id);
typedef bool (*amremove_function)(Relation rel, int nkey);
typedef IndexScanDesc (*ambeginscan_function)(Relation nrel, int nkeys, ScanKey key);
typedef bool (*amgetnext_function)(IndexScanDesc scan, enum ScanDirection dir);
typedef void (*amendscan_function)(Relation rel, int nkeys);
typedef void (*amvacuum_function)(Relation rel);

typedef struct IndexAm {
    ambuild_function ambuild;
    aminsert_function aminsert;
    amremove_function amremove;
    ambeginscan_function ambeginscan;
    amgetnext_function amgetnext;
    amendscan_function amendscan;
    amvacuum_function amvacuum;
} IndexAm;

extern IndexAm* GetIndexAmRoutine(Oid amhandler);

#endif
