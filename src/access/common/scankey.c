#include "access/scankey.h"
#include "util/fmgr.h"
/*
 * 初始化scankey
 * attrNumber	比较字段的位置
 */
void
ScanKeyInit(ScanKey entry, int attrNumber, enum StrategyNumber strategy, Datum datum, Oid funcOid) {
    memset(entry, 0, sizeof(struct ScanKeyData));

    entry->sk_att_no   = attrNumber;
    entry->sk_strategy = strategy;
    entry->sk_data     = datum;
    fmgr_info(funcOid, &entry->sk_func);
}