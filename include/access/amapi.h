/*
 * define all index access methods.
 */
#ifndef _amapi_h_
#define _amapi_h_

#include "mimi.h"
#include "access/genam.h"




void BuildEmpty(Relation rel);

bool Insert(Relation rel, int nkey, int ht_id);
bool Remove(Relation rel, int nkey);
IndexScanDesc BeginScan(Relation nrel, int nkeys, ScanKey key);
bool GetNext(IndexScanDesc scan, enum ScanDirection dir);
void EndScan(Relation rel, int nkeys);
void Vacuum(Relation rel);

#endif
