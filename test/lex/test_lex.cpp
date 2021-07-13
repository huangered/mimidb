#include "../g.hpp"

#include "lex/lexer.hpp"
#include <vector>
#include "sema/sema.hpp"
#include <stack>

TEST(Lexer, Lexer) {

    std::vector<LexTokenData*> arr;
    const char* a = "((()) ab 1234";
    Lexer* b = new Lexer(a, strlen(a));
    LexTokenData* token;
    while ((token = b->getLexerToken()) != nullptr) {
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

    
}