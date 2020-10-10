#include "../g.h"

_EXTERN_C
#include "parser/tokens.h"
#include "node/parsenode.h"
_END_EXTERN_C

// test the basic usage in buff mgr.
TEST(parser, basic)
{
	SelectStmt* raw = (SelectStmt*)raw_parse("select ( a,b,c ) from a;");
	EXPECT_TRUE(raw != NULL);
	EXPECT_EQ(raw->nodetag, NT_SelectStmt);
	EXPECT_STREQ(raw->relname, "a");
	EXPECT_EQ(3, raw->columns->length);
}

TEST(parser, basic_insert)
{
	InsertStmt* raw = (InsertStmt*)raw_parse("insert into s values ( a,b,c );");
	EXPECT_TRUE(raw != NULL);
	EXPECT_EQ(raw->nodetag, NT_InsertStmt);
	EXPECT_STREQ(raw->relname, "s");
	EXPECT_EQ(3, raw->columns->length);
}

TEST(parser, basic_create_table)
{
	CreateTableStmt* raw = (CreateTableStmt*)raw_parse("create table test ( a int, b text, c text );");
	EXPECT_TRUE(raw != NULL);
	EXPECT_EQ(raw->nodetag, NT_CreateTableStmt);
	EXPECT_STREQ(raw->relname, "test");
}