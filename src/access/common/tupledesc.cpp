#include "access/tupledesc.hpp"
#include "util/mctx.hpp"

TupleDescData::TupleDescData(int _natts) :natts{ _natts } {
    attrs = new FormData_mimi_attribute[_natts];
}

TupleDescData::TupleDescData(int _natts, Form_mimi_attribute _attrs) : natts{ _natts } {
    attrs = new FormData_mimi_attribute[_natts];
    for (int i{ 0 }; i < natts; i++) {
        memcpy(&attrs[i], &_attrs[i], sizeof(FormData_mimi_attribute));
    }
}

TupleDescData::~TupleDescData() {
    if (attrs != nullptr) {
        delete[] attrs;
    }
}

int
TupleDescData::GetNatts() {
    return natts;
}

Form_mimi_attribute
TupleDescData::GetNatt(int index) {
    return attrs + index;
}


/*
* 创建一个空的 tupledesc
*/
TupleDesc
CreateTempTupleDesc(int natts) {
    TupleDesc desc = new TupleDescData(natts);
    return desc;
}

/*
create a tupledesc object by attrs
*/
TupleDesc
CreateTupleDesc(int natts, Form_mimi_attribute attrs) {
    TupleDesc tupdesc = new TupleDescData(natts, attrs);
    return tupdesc;
}

/*
free tupledesc object
*/
void
FreeTupleDesc(TupleDesc tupdesc) {
    delete tupdesc;
}