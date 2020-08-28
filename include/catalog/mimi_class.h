#ifndef _mimi_class_h_
#define _mimi_class_h_

#include "mimi.h"

typedef struct FormData_mimi_class {
    Oid oid;
    char name[NAME_LIMIT];

    int relpages;   /* num of pages */
    int tuples;     /* num of tuples */
    char relkind;   /* relation type */
} FormData_mimi_class;

typedef FormData_mimi_class* Form_mimi_class;

#define     RELKIND_RELATION        'r'
#define     RELKIND_INDEX           'i'


#endif // !_mimi_class_h_
