#include "access/tupledesc.h"
#include "util/mctx.h"

TupleDesc CreateTempTupleDesc(int natts) {
    TupleDesc desc = palloc(offsetof(TupleDescData, attr) + natts * sizeof(FormData_mimi_attribute));
    desc->natts = natts;
    return desc;
}
