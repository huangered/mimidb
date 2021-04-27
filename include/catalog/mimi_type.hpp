#ifndef _mimi_type_hpp_
#define _mimi_type_hpp_

#include "mimi.hpp"

struct FormData_mimi_type {
    Oid oid;
    char typ_name[NAME_LIMIT];
    int typ_length;
    Oid typ_func;
};

typedef FormData_mimi_type* Form_mimi_type;

#endif // !_MIMI_TYPE_H_
