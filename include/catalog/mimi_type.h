#ifndef _MIMI_TYPE_H_
#define _MIMI_TYPE_H_

#include "mimi.h"

typedef struct FormData_mimi_am {
    Oid oid;
    char amname[NAME_LIMIT];
    char amhandler[NAME_LIMIT];
    char amtype;
} FormData_mimi_am;

typedef FormData_mimi_am* Form_mimi_am;

#endif // !_MIMI_TYPE_H_
