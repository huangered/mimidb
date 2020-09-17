#include "../g.h"

_EXTERN_C
#include "parser/tokens.h"
_END_EXTERN_C

// test the basic usage in buff mgr.
TEST(parser, basic)
{
	Node* raw = raw_parse("select s from a;");
	EXPECT_EQ(raw->nodetag, 1);
}