#ifndef _mimi_class_h_
#define _mimi_class_h_

#include "mimi.h"

typedef struct FormData_mimi_class {
    Oid oid;
    char name[64];
} FormData_mimi_class;

typedef FormData_mimi_class* Form_mimi_class;

#endif // !_mimi_class_h_
