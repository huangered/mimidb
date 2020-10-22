#ifndef _mimi_type_h_
#define _mimi_type_h_

#include "mimi.hpp"

typedef struct FormData_mimi_type {
    Oid oid;
    char typename[NAME_LIMIT];
    int length;
} FormData_mimi_type;

typedef FormData_mimi_type* Form_mimi_type;

#endif // !_mimi_class_h_
