#ifndef _tupledesc_hpp_
#define _tupledesc_hpp_

#include "catalog/mimi_attribute.h"

#define MAX_NATTS

struct TupleDescData {
    int natts;
    struct FormData_mimi_attribute attr[MAX_NATTS];
};

typedef struct TupleDescData* TupleDesc;

extern TupleDesc CreateTempTupleDesc(int natts);
extern TupleDesc CreateTupleDesc(int natts, Form_mimi_attribute attrs);

extern void FreeTupleDesc(TupleDesc tupdesc);

#endif // !_TupleDesc_h_
