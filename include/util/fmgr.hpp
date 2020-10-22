#ifndef _FMGR_H_
#define _FMGR_H_

#include "mimi.hpp"

#define MAX_ARGS 10

typedef struct FunctionCallInfoData* FunctionCallInfo;
typedef Datum (*MMFunction)(FunctionCallInfo fcinfo);

typedef struct FmgrInfo {
    Oid fn_id;
    MMFunction fn_addr;
} FmgrInfo;

typedef struct FunctionCallInfoData {
    MMFunction* flinfo;
    short nagrs;
    Datum args[MAX_ARGS];
}FunctionCallInfoData;

extern void fmgr_info(Oid functionId, FmgrInfo* finfo);

extern Datum DirectFunctionCall2Coll(MMFunction func, Datum arg1, Datum arg2);

#endif