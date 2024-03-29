
#include "../g.hpp"

#include "node/parsenode.hpp"

// test the basic usage in buff mgr.
TEST(parser, select_stmt) {
    SelectStmt* raw = (SelectStmt*)mison_parse("select a,b,c from a;");
    EXPECT_TRUE(raw != NULL);
    EXPECT_EQ(raw->nodetag, NT_SelectStmt);
    EXPECT_STREQ(raw->relname, "a");
    EXPECT_EQ(3, raw->columns->size());
}

TEST(parser, insert_stmt) {
    InsertStmt* raw = (InsertStmt*)mison_parse("insert into s values ( 123, 'a', 'jkl' );");
    EXPECT_TRUE(raw != NULL);
    EXPECT_EQ(raw->nodetag, NT_InsertStmt);
    EXPECT_STREQ(raw->relname, "s");
    EXPECT_EQ(3, raw->columns->size());
}

TEST(parser, insert_stmt2) {
    InsertStmt* raw = (InsertStmt*)mison_parse("insert into s values ( 123, 456 );");
    EXPECT_TRUE(raw != NULL);
    EXPECT_EQ(raw->nodetag, NT_InsertStmt);
    EXPECT_STREQ(raw->relname, "s");
    EXPECT_EQ(2, raw->columns->size());
}

TEST(parser, basic_create_table) {
    CreateTableStmt* raw = (CreateTableStmt*)mison_parse("create table test ( a int, b text, c text );");
    EXPECT_TRUE(raw != NULL);
    EXPECT_EQ(raw->nodetag, NT_CreateTableStmt);
    EXPECT_STREQ(raw->relname, "test");

    //    ColumnDef* param = (ColumnDef*)raw->columns->head->data.ptr_value;
    //    EXPECT_STREQ(param->colname, "c");

    //    TypeName* tname = param->typeName;
    //    EXPECT_STREQ(tname->name, "text");
}

TEST(parser, update_row) {
    UpdateStmt* raw = (UpdateStmt*)mison_parse("update test set a='a', b='b',c='c';");
    EXPECT_TRUE(raw != NULL);
    EXPECT_EQ(raw->nodetag, NT_UpdateStmt);
    EXPECT_STREQ(raw->relname, "test");
    EXPECT_EQ(3, raw->columns->size());
    EXPECT_TRUE(raw->where_cause == NULL);
}

TEST(parser, update_row_where) {
    UpdateStmt* raw = (UpdateStmt*)mison_parse("update test set a='a1', b='12', c=123 where a='asdf';");
    EXPECT_TRUE(raw != NULL);
    EXPECT_EQ(raw->nodetag, NT_UpdateStmt);
    EXPECT_STREQ(raw->relname, "test");
    EXPECT_EQ(3, raw->columns->size());
    EXPECT_TRUE(raw->where_cause != NULL);
}
