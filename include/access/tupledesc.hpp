#ifndef _tupledesc_hpp_
#define _tupledesc_hpp_

#include "catalog/mimi_attribute.hpp"

#define MAX_NATTS

class TupleDescData {
    int natts;
    Form_mimi_attribute attrs;
public:
    TupleDescData(int _natts);
    TupleDescData(int _natts, Form_mimi_attribute _attrs);
    ~TupleDescData();

    int GetNatts();
    Form_mimi_attribute GetNatt(int index);
};

typedef TupleDescData* TupleDesc;

extern TupleDesc CreateTempTupleDesc(int natts);
extern TupleDesc CreateTupleDesc(int natts, Form_mimi_attribute attrs);

extern void FreeTupleDesc(TupleDesc tupdesc);

#endif // !_TupleDesc_h_
