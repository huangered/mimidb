//#include "../g.hpp"
//#include "lex/lexer.hpp"
//#include "sema/sema.hpp"
//#include "sema/rulereader.hpp"
//
// TEST(Sema, GroupKeyTest1) {
//    group_key k1{ 1, nullptr, {} };
//    group_key k2{ 2, nullptr, {} };
//
//    EXPECT_TRUE(k1 < k2);
//}
//
// TEST(Sema, GroupKeyTest2) {
//    SemaToken t1 = new SemaTokenData{ 1, true, "" };
//    SemaToken t2 = new SemaTokenData{ 2, true, "" };
//
//    group_key k1{ 1, t1, {} };
//    group_key k2{ 1, t2, {} };
//
//    EXPECT_TRUE(k1 < k2);
//
//    delete t1;
//    delete t2;
//}
//
// TEST(Sema, GroupKeyTest3) {
//    SemaToken t1 = new SemaTokenData{ 1, true, "" };
//    SemaToken t2 = new SemaTokenData{ 2, true, "" };
//
//    group_key k1{ 1, t1, {} };
//    group_key k2{ 1, t2, {} };
//
//    EXPECT_TRUE(k1 < k2);
//
//    delete t1;
//    delete t2;
//}
//
// TEST(Sema, tok_eq) {
//    std::set<Tok> a;
//    std::set<Tok> b;
//
//    a.insert(Tok::comma);
//    b.insert(Tok::comma);
//
//    EXPECT_TRUE(a == b);
//}
//
// TEST(Sema, tok_ne) {
//    std::set<Tok> a;
//    std::set<Tok> b;
//
//    a.insert(Tok::comma);
//    b.insert(Tok::kw_select);
//
//    EXPECT_TRUE(a != b);
//}
//
//#ifdef _WIN32
// const char* path = "C:\\work\\mimidb\\sql.rule";
//#else
// const char* path = "./sql.rule";
//#endif
//
// TEST(Sema, select_test) {
//    auto rList = ReadRules(path);
//
//    const char* str = "select * from asdf;";
//
//    Lexer lexer(str, strlen(str));
//
//    LexToken t;
//    std::vector<LexToken> data;
//    while ((t = lexer.GetLexerToken()) != nullptr) {
//        if (t->tok != Tok::whitespace) {
//            data.push_back(t);
//        }
//    }
//    data.push_back(EndLexToken);
//
//    Parser parser(rList.rules);
//    parser.GenerateParseTable();
//    auto n = parser.Parse(data);
//    EXPECT_TRUE(n.first);
//    Node node = n.second;
//    EXPECT_TRUE(node != nullptr);
//
//    delete n.second;
//}
//
// TEST(Sema, select_where_test) {
//    auto rList = ReadRules(path);
//
//    const char* str = "select * from asdf where;";
//
//    Lexer lexer(str, strlen(str));
//
//    LexToken t;
//    std::vector<LexToken> data;
//    while ((t = lexer.GetLexerToken()) != nullptr) {
//        if (t->tok != Tok::whitespace) {
//            data.push_back(t);
//        }
//    }
//    data.push_back(EndLexToken);
//
//    Parser parser(rList.rules);
//    parser.GenerateParseTable();
//    auto n = parser.Parse(data);
//    EXPECT_TRUE(n.first);
//    Node node = n.second;
//    EXPECT_TRUE(node != nullptr);
//
//    delete n.second;
//}
//
// TEST(Sema, select_fail_test) {
//    auto rList = ReadRules(path);
//
//    const char* str = "select * from asdf where a;";
//
//    Lexer lexer(str, strlen(str));
//
//    LexToken t;
//    std::vector<LexToken> data;
//    while ((t = lexer.GetLexerToken()) != nullptr) {
//        if (t->tok != Tok::whitespace) {
//            data.push_back(t);
//        }
//    }
//    data.push_back(EndLexToken);
//
//    Parser parser(rList.rules);
//    parser.GenerateParseTable();
//    auto n = parser.Parse(data);
//    EXPECT_FALSE(n.first);
//    Node node = n.second;
//    EXPECT_EQ(node, nullptr);
//}
//
//
// TEST(Sema, lex_init) {
//    auto rList = ReadRules("C:\\work\\mimidb\\sql-lex.rule");
//
//    Parser parser(rList.rules);
//    parser.GenerateParseTable();
//    parser.GenerateCppCode("lexggg.h");
//}