#ifndef _TupleDesc_h_
#define _TupleDesc_h_

#include "catalog/mimi_attribute.hpp"

#define MAX_NATTS   256

typedef struct TupleDescData {
    int natts;
    FormData_mimi_attribute attr[MAX_NATTS];
} TupleDescData;

typedef struct TupleDescData* TupleDesc;

extern TupleDesc CreateTempTupleDesc(int natts);
extern TupleDesc CreateTupleDesc(int natts, Form_mimi_attribute* attrs);

extern void FreeTupleDesc(TupleDesc tupdesc);

#endif // !_TupleDesc_h_
