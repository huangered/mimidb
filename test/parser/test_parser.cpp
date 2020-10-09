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

}

TEST(parser, basic_insert)
{
	InsertStmt* raw = (InsertStmt*)raw_parse("insert into s values ( a,b,c );");
	EXPECT_TRUE(raw != NULL);
	EXPECT_EQ(raw->nodetag, NT_InsertStmt);
	EXPECT_STREQ(raw->relname, "s");
}