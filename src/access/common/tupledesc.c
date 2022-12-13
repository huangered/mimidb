#include "access/tupledesc.h"

/*
 * 创建一个空的 tupledesc
 */
TupleDesc
CreateTempTupleDesc(int natts) {
    TupleDesc desc = (TupleDesc)palloc0(offsetof(TupleDescData, attr) + natts * sizeof(FormData_mimi_attribute));
    desc->natts    = natts;
    return desc;
}

/*
create a tupledesc object by attrs
*/
TupleDesc
CreateTupleDesc(int natts, Form_mimi_attribute attrs) {
    TupleDesc tupdesc = CreateTempTupleDesc(natts);
    // copy the attrs;
    for (int i{ 0 }; i < natts; i++) {
        memcpy(&tupdesc->attr[i], &attrs[i], sizeof(FormData_mimi_attribute));
    }
    return tupdesc;
}

/*
free tupledesc object
*/
void
FreeTupleDesc(TupleDesc tupdesc) {
    pfree(tupdesc);
}