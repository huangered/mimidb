#include "access/scankey.hpp"

static FmgrInfo searchFuncByOid(Oid oid);
/*
* 初始化scankey
* attrNumber	比较字段的位置
*/
void
ScanKeyInit(ScanKey entry, int attrNumber, StrategyNumber strategy, Datum datum, Oid funcOid) {
	entry->sk_att_no = attrNumber;
	entry->sk_strategy = strategy;
	entry->sk_data = datum;
	entry->sk_func = searchFuncByOid(funcOid);
}

FmgrInfo
searchFuncByOid(Oid oid) {
	FmgrInfo info;
	return info;
}