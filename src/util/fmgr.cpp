#include "util/fmgr.hpp"
#include "util/builtins.hpp"

typedef struct FmgrBuildin {
    Oid foid; /* OID of the function */
    const char* name;
    Method func;
} FmgrBuildin;

static FmgrBuildin fmgr_buildins[] = {
    {INT8CMP_OID, "int8cmp", int8cmp},
    {INT16CMP_OID, "int16cmp", int16cmp},
    {INT32CMP_OID, "int32cmp", int32cmp},
    {OIDEQ_OID, "oideq", oideq},

};

static FmgrBuildin*
fmgr_isbuildin(Oid functionId) {
    return &fmgr_buildins[functionId];
}

void
fmgr_info(Oid functionId, FmgrInfo* finfo) {
    const FmgrBuildin* fbp;
    finfo->fn_id = 0;

    if ((fbp = fmgr_isbuildin(functionId)) != nullptr) {
        finfo->fn_method = fbp->func;
        finfo->fn_id = functionId;
        return;
    }

    // 从syscache里查找
}

Datum
DirectFunctionCall2Coll(Method func, Datum arg1, Datum arg2) {
    FunctionCallInfoData fdata{};
    fdata.flinfo = &func;
    fdata.nargs = 2;
    fdata.args[0] = arg1;
    fdata.args[1] = arg2;
    Datum result = (*fdata.flinfo)(&fdata);
    return result;
}