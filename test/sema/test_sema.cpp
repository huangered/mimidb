#include "../g.hpp"
#include "lex/lexer.hpp"
#include "sema/sema.hpp"

TEST(Sema, FirstSetTest) {

    LexToken a1 = new LexTokenData{Tok::Plus, "+"};
    LexToken a2 = new LexTokenData{Tok::Identifier, "id"};
    LexToken a3 = new LexTokenData{Tok::Eof, "$"};

    SemaToken Q = new SemaTokenData{0, true, "Q"};
    SemaToken S = new SemaTokenData{1, true, "S"};
    SemaToken C = new SemaTokenData{2, true, "C"};
    SemaToken t1 = new SemaTokenData{3, false, a1};
    SemaToken t2 = new SemaTokenData{4, false, a2};
    SemaToken eof = new SemaTokenData{5, false, a3};

    LexTokenData* l1 = new LexTokenData{Tok::Identifier};
    LexTokenData* l2 = new LexTokenData{Tok::Identifier};
    LexTokenData* l3 = new LexTokenData{Tok::Eof};

    SimpleRule r1 = make_rule(0, Q, {S});
    SimpleRule r2 = make_rule(1, S, {C, C});
    SimpleRule r3 = make_rule(2, C, {t1, C});
    SimpleRule r4 = make_rule(3, C, {t2});

    std::vector<SimpleRule> rules{r1, r2, r3, r4};

    Parser parser(rules, {t1, t2, eof}, {Q, S, C});
    parser.GenerateParseTable();
    Node n = parser.Parse({l1, l2, l3});

    EXPECT_TRUE(n != nullptr);
    EXPECT_EQ(n->getToken()->id, S->id);
    for (SimpleRule r : rules) {
        delete r;
    }

    delete Q;
    delete S;
    delete C;
    delete t1;
    delete t2;

    delete a1;
    delete a2;
    delete a3;
}
