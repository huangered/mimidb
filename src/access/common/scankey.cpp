#include "access/scankey.hpp"
#include "util/fmgr.hpp"

ScanKeyData::ScanKeyData(){}
/*
* 初始化scankey
* attrNumber	比较字段的位置
*/
ScanKeyData::ScanKeyData(int attrNumber, StrategyNumber strategy, Datum datum, Oid funcOid) {
	sk_att_no = attrNumber;
	sk_strategy = strategy;
	sk_data = datum;
	fmgr_info(funcOid, &sk_func);
}