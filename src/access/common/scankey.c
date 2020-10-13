#include "access/scankey.h"

/*
初始化scankey
*/
void
ScanKeyInit(ScanKey entry, int attrNumber, StrategyNumber strategy, Datum datum, FmgrInfo func) {
	entry->sk_att_no = attrNumber;
	entry->sk_strategy = strategy;
	entry->sk_data = datum;
	entry->sk_func = func;
}