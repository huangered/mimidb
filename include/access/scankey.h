#ifndef _scankey_hpp_
#define _scankey_hpp_

#include "mimi.h"
#include "access/strategynumber.h"
#include "util/fmgr.h"

struct ScanKeyData {
    int sk_att_no;              // 表和index里第几列
    struct FmgrInfo sk_func;           // 比较函数
   enum StrategyNumber sk_strategy; // 比较方式
    Datum sk_data;              // 比较数据
};

typedef struct ScanKeyData* ScanKey;

// 初始化 scankey
void ScanKeyInit(ScanKey entry, int attrNumber, enum StrategyNumber strategy, Datum datum, Oid funcOid);

#endif // !_scankey_hpp_
