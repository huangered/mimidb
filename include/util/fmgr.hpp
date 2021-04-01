#ifndef _FMGR_H_
#define _FMGR_H_

#include "mimi.hpp"

#define MAX_ARGS 10

typedef struct FunctionCallInfoData* FunctionCallInfo;

typedef Datum (*Method)(FunctionCallInfo fc_info);

struct FmgrInfo {
    Oid fn_id;
    Method fn_method;
};

struct FunctionCallInfoData {
    Method* flinfo;
    short nagrs;
    Datum args[MAX_ARGS];
};

extern void fmgr_info(Oid functionId, FmgrInfo* fn_info);

extern Datum DirectFunctionCall2Coll(Method func, Datum arg1, Datum arg2);

#endif