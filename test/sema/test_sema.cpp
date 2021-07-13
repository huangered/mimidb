#include "../g.hpp"
#include "lex/lexer.hpp"
#include "sema/sema.hpp"

TEST(Sema, FirstSetTest) {

	SemaToken Q = new SemaTokenData{ 0, true, "Q" };
	SemaToken S = new SemaTokenData{ 1, true, "S" };
	SemaToken C = new SemaTokenData{ 2, true, "C" };
	SemaToken t1 = new SemaTokenData{ 3, false,{Tok::Plus, "+"} };
	SemaToken t2 = new SemaTokenData{ 4, false, {Tok::Identifier, "id"} };
	SemaToken eof = new SemaTokenData{ 5, false, {Tok::Money, "$"} };

	LexTokenData* l1 = new LexTokenData{ Tok::Identifier };
	LexTokenData* l2 = new LexTokenData{ Tok::Identifier };
	LexTokenData* l3 = new LexTokenData{ Tok::Money };

	Rule1 r1 = make_rule(0, Q, { S });
	Rule1 r2 = make_rule(1, S, { C, C });
	Rule1 r3 = make_rule(2, C, { t1, C });
	Rule1 r4 = make_rule(3, C, { t2 });

	std::vector<Rule1> rules{ r1,r2,r3,r4 };

	Parser parser(rules, { t1, t2, eof }, { Q, S,C });
	parser.GenerateParseTable();
	Node n = parser.Parse({ l1, l2 , l3 });

	EXPECT_TRUE(n != nullptr);

	for (Rule1 r : rules) {
		delete r;
	}

	delete Q;
	delete S;
	delete C;
	delete t1;
	delete t2;
}
