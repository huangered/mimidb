#ifndef _MIMI_AM_H_
#define _MIMI_AM_H_

#include "mimi.h"

typedef struct FormData_mimi_type {
    Oid oid;
    char typ_name[NAME_LIMIT];
    int typ_length;
} FormData_mimi_type;

typedef FormData_mimi_type* Form_mimi_type;

#endif // !_MIMI_AM_H_
