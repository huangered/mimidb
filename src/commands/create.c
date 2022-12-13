/*
 * create table实现
 */
#include "commands/create.h"
#include "catalog/catalog.h"
#include "catalog/heap.h"
#include "catalog/index.h"
#include "commands/indexcmds.h"

// static TupleDesc formTupleDesc(List* columns);
// static void formAttr(FormData_mimi_attribute* attr, ColumnDef* def);

/*
创建表
*/
void
DefineRelation(struct CreateTableStmt* stmt) {
    Relation heap_rel;
    // 创建堆表
    const char* name = stmt->relname;
    Oid id           = GetNewOid();
    //    TupleDesc tupdesc = formTupleDesc(stmt->columns);
    //    heap_rel          = heap_create_with_catalog(name, id, tupdesc);

    // 创建索引
}

// 从 column def 创建 attribute对象
/*
TupleDesc
formTupleDesc(List* columns) {
    ListCell* cell;
    ColumnDef* columndef;
    int natts = list_len(columns);

    TupleDesc tupdesc = CreateTempTupleDesc(natts);
    for (cell = list_first_elem(columns); cell != nullptr; cell = list_next_elem(cell)) {
        columndef = (ColumnDef*)cell->data.ptr_value;

        // 生产 attr 对象
        formAttr(tupdesc->attr, columndef);
    }
    return tupdesc;
}

void
formAttr(FormData_mimi_attribute* attr, ColumnDef* def) {
    attr->typid   = def->typeName->typeOid;
    attr->att_len = 255;
    // memcpy(attr->attname, def->colname, attr->attlen);
}
*/
