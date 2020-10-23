#ifndef _MIMI_AM_H_
#define _MIMI_AM_H_

#include "mimi.h"

typedef struct FormData_mimi_am {
    Oid oid;
    char am_name[NAME_LIMIT];
    char am_handler[NAME_LIMIT];
    char am_type;
} FormData_mimi_am;

typedef FormData_mimi_am* Form_mimi_am;


#endif // !_MIMI_AM_H_
