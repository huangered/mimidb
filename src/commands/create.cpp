/*
* create table实现
*/
#include "commands/create.hpp"
#include "catalog/catalog.hpp"
#include "catalog/heap.hpp"
#include "catalog/index.hpp"
#include "commands/indexcmds.hpp"
#include "util/mctx.hpp"

static TupleDesc formTupleDesc(List* columns);
static void formAttr(FormData_mimi_attribute* attr, ColumnDef* def);

/*
创建表
*/
void
DefineRelation(CreateTableStmt* stmt) {
	const char* name = stmt->relname;
	Oid id = GetNewOid();
	TupleDesc tupdesc = (TupleDesc)formTupleDesc(stmt->columns);
	heap_create_with_catalog(name, id, tupdesc);
}

TupleDesc
formTupleDesc(List* columns) {
	ListCell* cell;
	ColumnDef* columndef;

	TupleDesc tupdesc = (TupleDesc)palloc(sizeof(TupleDescData));
	tupdesc->natts = list_len(columns);
	for (cell = list_first_elem(columns); cell!=NULL; cell=list_next_elem(cell)) {
		columndef = (ColumnDef*)cell->data.ptr_value;

		// form attr
		formAttr(tupdesc->attr, columndef);
	}
	return tupdesc;
}

void
formAttr(FormData_mimi_attribute* attr, ColumnDef* def) {
	attr->typid = def->typeName->typeOid;
	attr->att_len = 255;
	//memcpy(attr->attname, def->colname, attr->attlen);
}