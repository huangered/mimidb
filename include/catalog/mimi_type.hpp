#ifndef _mimi_am_h_
#define _mimi_am_h_

#include "mimi.hpp"

typedef struct FormData_mimi_am {
    Oid oid;
    char amname[NAME_LIMIT];
    char amhandler[NAME_LIMIT];
    char amtype;
} FormData_mimi_am;

typedef FormData_mimi_am* Form_mimi_am;

#endif // !_mimi_class_h_
