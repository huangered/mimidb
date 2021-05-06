#ifndef _buildins_h_
#define _buildins_h_

#include "mimi.hpp"
#include "util/fmgr.hpp"

#define INT8CMP_OID		0
#define INT16CMP_OID	1
#define INT32CMP_OID	2
#define OIDCMP_OID		3

// 各种int比较函数
Datum int8cmp(FunctionCallInfo fcinfo);
Datum int16cmp(FunctionCallInfo fcinfo);
Datum int32cmp(FunctionCallInfo fcinfo);

// oid 相关函数
Datum oidcmp(FunctionCallInfo fcinfo);
#endif