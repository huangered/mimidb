#ifndef _TupleDesc_h_
#define _TupleDesc_h_

#include "catalog/mimi_attribute.h"

#define MAX_NATTS   256

typedef struct TupleDescData {
    int natts;
    FormData_mimi_attribute attr[MAX_NATTS];
} TupleDescData;

typedef struct TupleDescData* TupleDesc;

#endif // !_TupleDesc_h_
