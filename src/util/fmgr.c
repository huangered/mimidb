#include "util/fmgr.h"
#include "util/builtins.h"

typedef struct FmgrBuildin {
    Oid			foid;			/* OID of the function */
    const char* name;
    MMFunction	func;
}FmgrBuildin;

const FmgrBuildin fmgr_buildins[] = {
    {INT8CMP_OID, "int8cmp", int8cmp},
    {INT16CMP_OID, "int16cmp", int16cmp},
    {INT32CMP_OID, "int32cmp", int32cmp},
    {OIDEQ_OID, "oideq", oideq},

};

static FmgrBuildin* fmgr_isbuildin(Oid functionId) {
    return &fmgr_buildins[functionId];
}

void
fmgr_info(Oid functionId, FmgrInfo* finfo) {
    const FmgrBuildin* fbp;
    finfo->fn_id = 0;

    if ((fbp = fmgr_isbuildin(functionId)) != NULL) {
        finfo->fn_addr = fbp->func;
        finfo->fn_id = functionId;
    }
}

Datum
DirectFunctionCall2Coll(MMFunction func, Datum arg1, Datum arg2) {
    FunctionCallInfoData fdata;
    fdata.flinfo = &func;
    fdata.nagrs = 2;
    fdata.args[0] = arg1;
    fdata.args[1] = arg2;
    Datum result = (*fdata.flinfo)(&fdata);
    return result;
}