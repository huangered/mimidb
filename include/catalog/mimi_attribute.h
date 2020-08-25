#ifndef _mimi_attribute_h_
#define _mimi_attribute_h_

#include "mimi.h"

typedef struct FormData_mimi_attribute {
    Oid oid;
    char name[NAME_LIMIT];
    int length;
    int type;
} FormData_mimi_attribute;

typedef FormData_mimi_attribute* Form_mimi_attribute;

#endif // !_mimi_class_h_
