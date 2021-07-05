#ifndef _scankey_hpp_
#define _scankey_hpp_

#include "access/strategynumber.hpp"
#include "util/fmgr.hpp"

class ScanKeyData {
public:
    int sk_att_no;              // 表和index里第几列
    FmgrInfo sk_func;           // 比较函数
    StrategyNumber sk_strategy;   // 比较方式
    Datum sk_data;              // 比较数据

public:
    ScanKeyData();
    // 初始化 scankey
    ScanKeyData(int attrNumber, StrategyNumber strategy, Datum datum, Oid funcOid);
};

typedef ScanKeyData* ScanKey;

#endif // !_scankey_hpp_

