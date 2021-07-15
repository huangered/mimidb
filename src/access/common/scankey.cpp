#include "access/scankey.hpp"
#include "util/fmgr.hpp"
/*
 * 初始化scankey
 * attrNumber	比较字段的位置
 */
void
ScanKeyInit(ScanKey entry, int attrNumber, StrategyNumber strategy, Datum datum, Oid funcOid) {
    memset(entry, 0, sizeof(ScanKeyData));

    entry->sk_att_no = attrNumber;
    entry->sk_strategy = strategy;
    entry->sk_data = datum;
    fmgr_info(funcOid, &entry->sk_func);
}