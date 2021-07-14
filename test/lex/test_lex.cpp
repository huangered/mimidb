#include "../g.hpp"

#include "lex/lexer.hpp"
#include <vector>
#include "sema/sema.hpp"
#include <stack>

TEST(Lexer, Lexer) {

    std::vector<LexToken> arr;
    const char* a = "((()) ab 1234";
    Lexer* b = new Lexer(a, strlen(a));
    LexToken token;
    while ((token = b->GetLexerToken()) != nullptr) {
        arr.push_back(token);
    }

    EXPECT_EQ(Tok::LeftBrace, arr[0]->tok);
    EXPECT_EQ(Tok::LeftBrace, arr[1]->tok);
    EXPECT_EQ(Tok::LeftBrace, arr[2]->tok);
    EXPECT_EQ(Tok::RightBrace, arr[3]->tok);
    EXPECT_EQ(Tok::RightBrace, arr[4]->tok);

    for (auto i : arr) {
        delete i;
    }

    delete b;


}

TEST(Lexer, FirstSet_Test) {

    std::vector<LexToken> arr;
    const char* a = "select * from abc;";
    Lexer* b = new Lexer(a, strlen(a));
    LexToken token;
    while ((token = b->GetLexerToken()) != nullptr) {
        if(token->tok == Tok::WhiteSpace) {
            delete token;
        } else {
            arr.push_back(token);
        }
    }

    EXPECT_EQ(Tok::Select, arr[0]->tok);
    EXPECT_EQ(Tok::Mul, arr[1]->tok);
    EXPECT_EQ(Tok::From, arr[2]->tok);
    EXPECT_EQ(Tok::Identifier, arr[3]->tok);
    EXPECT_EQ(Tok::Semicolon, arr[4]->tok);

    for (auto i : arr) {
        delete i;
    }

    delete b;
}
