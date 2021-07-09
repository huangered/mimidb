#include "../g.hpp"

#include "lex/lexer.hpp"
#include <vector>
#include "sema/sema.hpp"
#include <stack>

TEST(Lexer, Lexer) {

    std::vector<LexToken*> arr;
    const char* a = "((()) ab 1234";
    Lexer* b = new Lexer(a, strlen(a));
    LexToken* token;
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

TEST(Lexer, Directory_Test) {

    int* q = new int{ 3 };
    Directory<int, int, int*> a1;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            a1.put(i, j, new int{ 3 });
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            auto q = a1.get(i, j);
            EXPECT_EQ(*q.second, 3);
        }
    }

    auto q123 = a1.get(100, 100);
    EXPECT_FALSE(q123.first);
}