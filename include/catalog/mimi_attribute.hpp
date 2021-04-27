#ifndef _mimi_attribute_h_
#define _mimi_attribute_h_

#include "mimi.hpp"

/*
mimi_attribute 表描述
*/
struct FormData_mimi_attribute {
    Oid att_relid;
    char att_name[NAME_LIMIT];
    int att_len;
    int att_order;  // att的位置，从0开始
    Oid typ_id;
};

typedef FormData_mimi_attribute* Form_mimi_attribute;

#endif // !_mimi_class_h_
