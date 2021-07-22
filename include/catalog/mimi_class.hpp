#ifndef _mimi_class_h_
#define _mimi_class_h_

#include "mimi.hpp"

typedef struct FormData_mimi_class {
    Oid oid;
    char relname[NAME_LIMIT];
    char relkind; /* relation type */
    int relpages; /* num of pages */
    int tuples;   /* num of tuples */
    Oid relam;    /* 索引类型，如果不是索引，为0 */
    Oid relfilenode;
} FormData_mimi_class;

typedef FormData_mimi_class* Form_mimi_class;

#define RELKIND_RELATION            'r'
#define RELKIND_INDEX               'i'

#define MIMI_CLASS_OID_LOCATION     1
#define MIMI_CLASS_RELNAME_LOCATION 2

#endif // !_mimi_class_h_
