#ifndef _mimi_index_hpp_
#define _mimi_index_hpp_

#include "mimi.h"

struct FormData_mimi_index {
    Oid index_id;    /* index 的 relation id */
    Oid index_relid; /* index 索引的 relation id */
    int index_natts; /* index 的属性数 */
};

typedef FormData_mimi_index* Form_mimi_index;

#endif // !_mimi_class_h_
