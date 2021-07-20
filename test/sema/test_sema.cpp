#include "../g.hpp"
#include "lex/lexer.hpp"
#include "sema/sema.hpp"
#include "sema/rulereader.hpp"

TEST(Sema, GroupKeyTest1) {
    group_key k1{ 1, nullptr, {} };
    group_key k2{ 2, nullptr, {} };

    EXPECT_TRUE(k1 < k2);
}

TEST(Sema, GroupKeyTest2) {
    SemaToken t1 = new SemaTokenData(1, true, "");
    SemaToken t2 = new SemaTokenData(2, true, "");

    group_key k1{ 1, t1, {} };
    group_key k2{ 1, t2, {} };

    EXPECT_TRUE(k1 < k2);


    delete t1;
    delete t2;
}


TEST(Sema, GroupKeyTest3) {
    SemaToken t1 = new SemaTokenData(1, true, "");
    SemaToken t2 = new SemaTokenData(2, true, "");

    group_key k1{ 1, t1, {} };
    group_key k2{ 1, t2, {} };

    EXPECT_TRUE(k1 < k2);

    delete t1;
    delete t2;
}

TEST(Sema, tok_eq) {
    std::set<Tok> a;
    std::set<Tok> b;

    a.insert(Tok::comma);
    
    b.insert(Tok::comma);

    EXPECT_TRUE(a == b);
}

TEST(Sema, tok_ne) {
    std::set<Tok> a;
    std::set<Tok> b;

    a.insert(Tok::comma);

    b.insert(Tok::kw_select);

    EXPECT_TRUE(a != b);
}
/*
TEST(Sema, select_test) {
    auto rList = ReadRules("C:\\work\\mimidb\\sql.rule");
    EXPECT_TRUE(rList.size(), 17);

    const char* str = "select * from asdf;select * from asdf;";

    Lexer lexer(str, strlen(str));

    LexToken t;
    std::vector<LexToken> data;
    while ((t = lexer.GetLexerToken()) != nullptr) {
        if (t->tok != Tok::whitespace) {
            data.push_back(t);
        }
    }
    data.push_back(EndLexToken);
    Parser parser(rList);
    parser.GenerateParseTable();
    Node n = parser.Parse(data);
    EXPECT_TRUE(n != nullptr);

    delete n;
}
*/