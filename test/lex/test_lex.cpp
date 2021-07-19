#include "../g.hpp"

#include "lex/lexer.hpp"
#include <vector>
#include "sema/sema.hpp"
#include <stack>

TEST(Lexer, Lexer) {

    std::vector<LexTokenData*> arr;
    const char* a = "((()) ab 1234";
    Lexer* b = new Lexer(a, strlen(a));
    LexToken token;
    while ((token = b->GetLexerToken()) != nullptr) {
        arr.push_back(token);
    }

    EXPECT_EQ(Tok::l_brace, arr[0]->tok);
    EXPECT_EQ(Tok::l_brace, arr[1]->tok);
    EXPECT_EQ(Tok::l_brace, arr[2]->tok);
    EXPECT_EQ(Tok::r_brace, arr[3]->tok);
    EXPECT_EQ(Tok::r_brace, arr[4]->tok);

    for (auto i : arr) {
        delete i;
    }

    delete b;
}

TEST(Lexer, Lexer1) {
    std::vector<LexToken> arr;
    const char* a = "select * from abc;";
    Lexer* b = new Lexer(a, strlen(a));
    LexToken token;
    while ((token = b->GetLexerToken()) != nullptr) {
        if (token->tok == Tok::whitespace) {
            delete token;
        } else {
            arr.push_back(token);
        }
    }

    EXPECT_EQ(Tok::kw_select, arr[0]->tok);
    EXPECT_EQ(Tok::mul, arr[1]->tok);
    EXPECT_EQ(Tok::kw_from, arr[2]->tok);
    EXPECT_EQ(Tok::identifier, arr[3]->tok);
    EXPECT_EQ(Tok::semicolon, arr[4]->tok);

    for (auto i : arr) {
        delete i;
    }

    delete b;
}
