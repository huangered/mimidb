#ifndef _buildins_h_
#define _buildins_h_

#include "mimi.h"
#include "util/fmgr.h"

#define INT8CMP_OID  0
#define INT16CMP_OID 1
#define INT32CMP_OID 2
#define OIDEQ_OID    3

// 各种int比较函数
extern Datum int8cmp(FunctionCallInfo fcinfo);
extern Datum int16cmp(FunctionCallInfo fcinfo);
extern Datum int32cmp(FunctionCallInfo fcinfo);

// oid 相关函数
extern Datum oideq(FunctionCallInfo fcinfo);
#endif