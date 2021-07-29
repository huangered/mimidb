#ifndef _p_test_hpp_
#define _p_test_hpp_
#include <iostream>
#include <stack>
#include <vector>
#include "sema/gogo.hpp"
#include "lex/TokenKinds.hpp"
#include "sema/sema.hpp"
using namespace std;

static bool eatToken(std::stack<int>& states, std::stack<Node>& syms, std::stack<LexToken>& input, bool* acc);
static bool reduce(std::stack<int>& states, std::stack<Node>& syms, bool r_state, int r_id);
Node raw_parse(const char* str);

Node
raw_parse(const char* str) {
    Lexer lexer(str, strlen(str));
    LexToken t;
    std::vector<LexToken> data;
    while ((t = lexer.GetLexerToken()) != nullptr) {
        if (t->tok != Tok::whitespace) {
            data.push_back(t);
        }
    }
    data.push_back(EndLexToken);

    Node node{ nullptr };
    std::stack<int> state_stack;
    std::stack<Node> token_stack;
    std::stack<LexToken> input_stack;

    state_stack.push(0);

    for (auto iter = data.rbegin(); iter != data.rend(); iter++) {
        input_stack.push(*iter);
    }

    bool acc{};
    while (!acc) {
        bool op = eatToken(state_stack, token_stack, input_stack, &acc);

        if (!op) {
            std::cout << " no action " << std::endl;
            break;
        }
    }
    if (acc) {
        node = token_stack.top();
    } else {
        while (!token_stack.empty()) {
            node = token_stack.top();
            token_stack.pop();
            delete node;
            node = nullptr;
        }
    }
    return node;
}
bool
eatToken(std::stack<int>& states, std::stack<Node>& syms, std::stack<LexToken>& input, bool* acc) {
    int curStateId = states.top();
    LexToken token = input.top();
    bool r_acc;
    bool r_state;
    int r_id;
    bool r_find{ false };
    if (0 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 10;
        r_find  = true;
    }
    if (0 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 11;
        r_find  = true;
    }
    if (0 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 9;
        r_find  = true;
    }
    if (0 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 12;
        r_find  = true;
    }
    if (1 == curStateId && 0 == token->tok) {
        r_acc   = 1;
        r_state = 0;
        r_id    = 0;
        r_find  = true;
    }
    if (2 == curStateId && 0 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 1;
        r_find  = true;
    }
    if (2 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 10;
        r_find  = true;
    }
    if (2 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 11;
        r_find  = true;
    }
    if (2 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 9;
        r_find  = true;
    }
    if (2 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 12;
        r_find  = true;
    }
    if (3 == curStateId && 0 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 3;
        r_find  = true;
    }
    if (3 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 3;
        r_find  = true;
    }
    if (3 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 3;
        r_find  = true;
    }
    if (3 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 3;
        r_find  = true;
    }
    if (3 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 3;
        r_find  = true;
    }
    if (4 == curStateId && 0 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 4;
        r_find  = true;
    }
    if (4 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 4;
        r_find  = true;
    }
    if (4 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 4;
        r_find  = true;
    }
    if (4 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 4;
        r_find  = true;
    }
    if (4 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 4;
        r_find  = true;
    }
    if (5 == curStateId && 0 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 5;
        r_find  = true;
    }
    if (5 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 5;
        r_find  = true;
    }
    if (5 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 5;
        r_find  = true;
    }
    if (5 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 5;
        r_find  = true;
    }
    if (5 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 5;
        r_find  = true;
    }
    if (6 == curStateId && 0 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 6;
        r_find  = true;
    }
    if (6 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 6;
        r_find  = true;
    }
    if (6 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 6;
        r_find  = true;
    }
    if (6 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 6;
        r_find  = true;
    }
    if (6 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 6;
        r_find  = true;
    }
    if (7 == curStateId && 0 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 7;
        r_find  = true;
    }
    if (7 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 7;
        r_find  = true;
    }
    if (7 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 7;
        r_find  = true;
    }
    if (7 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 7;
        r_find  = true;
    }
    if (7 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 7;
        r_find  = true;
    }
    if (8 == curStateId && 0 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 8;
        r_find  = true;
    }
    if (8 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 8;
        r_find  = true;
    }
    if (8 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 8;
        r_find  = true;
    }
    if (8 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 8;
        r_find  = true;
    }
    if (8 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 8;
        r_find  = true;
    }
    if (9 == curStateId && 30 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 14;
        r_find  = true;
    }
    if (9 == curStateId && 31 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 15;
        r_find  = true;
    }
    if (10 == curStateId && 4 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 19;
        r_find  = true;
    }
    if (10 == curStateId && 15 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 18;
        r_find  = true;
    }
    if (11 == curStateId && 26 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 20;
        r_find  = true;
    }
    if (12 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 29;
        r_find  = true;
    }
    if (12 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 30;
        r_find  = true;
    }
    if (12 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 28;
        r_find  = true;
    }
    if (12 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 31;
        r_find  = true;
    }
    if (13 == curStateId && 0 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 2;
        r_find  = true;
    }
    if (13 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 2;
        r_find  = true;
    }
    if (13 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 2;
        r_find  = true;
    }
    if (13 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 2;
        r_find  = true;
    }
    if (13 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 2;
        r_find  = true;
    }
    if (14 == curStateId && 15 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 33;
        r_find  = true;
    }
    if (15 == curStateId && 15 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 35;
        r_find  = true;
    }
    if (16 == curStateId && 8 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 38;
        r_find  = true;
    }
    if (16 == curStateId && 9 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 36;
        r_find  = true;
    }
    if (16 == curStateId && 24 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 37;
        r_find  = true;
    }
    if (17 == curStateId && 8 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 16;
        r_find  = true;
    }
    if (17 == curStateId && 9 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 16;
        r_find  = true;
    }
    if (17 == curStateId && 24 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 16;
        r_find  = true;
    }
    if (18 == curStateId && 8 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 17;
        r_find  = true;
    }
    if (18 == curStateId && 9 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 17;
        r_find  = true;
    }
    if (18 == curStateId && 24 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 17;
        r_find  = true;
    }
    if (19 == curStateId && 8 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 18;
        r_find  = true;
    }
    if (19 == curStateId && 9 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 18;
        r_find  = true;
    }
    if (19 == curStateId && 24 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 18;
        r_find  = true;
    }
    if (20 == curStateId && 15 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 40;
        r_find  = true;
    }
    if (21 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 29;
        r_find  = true;
    }
    if (21 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 30;
        r_find  = true;
    }
    if (21 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 28;
        r_find  = true;
    }
    if (21 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 31;
        r_find  = true;
    }
    if (21 == curStateId && 36 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 42;
        r_find  = true;
    }
    if (22 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 3;
        r_find  = true;
    }
    if (22 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 3;
        r_find  = true;
    }
    if (22 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 3;
        r_find  = true;
    }
    if (22 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 3;
        r_find  = true;
    }
    if (22 == curStateId && 36 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 3;
        r_find  = true;
    }
    if (23 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 4;
        r_find  = true;
    }
    if (23 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 4;
        r_find  = true;
    }
    if (23 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 4;
        r_find  = true;
    }
    if (23 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 4;
        r_find  = true;
    }
    if (23 == curStateId && 36 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 4;
        r_find  = true;
    }
    if (24 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 5;
        r_find  = true;
    }
    if (24 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 5;
        r_find  = true;
    }
    if (24 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 5;
        r_find  = true;
    }
    if (24 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 5;
        r_find  = true;
    }
    if (24 == curStateId && 36 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 5;
        r_find  = true;
    }
    if (25 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 6;
        r_find  = true;
    }
    if (25 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 6;
        r_find  = true;
    }
    if (25 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 6;
        r_find  = true;
    }
    if (25 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 6;
        r_find  = true;
    }
    if (25 == curStateId && 36 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 6;
        r_find  = true;
    }
    if (26 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 7;
        r_find  = true;
    }
    if (26 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 7;
        r_find  = true;
    }
    if (26 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 7;
        r_find  = true;
    }
    if (26 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 7;
        r_find  = true;
    }
    if (26 == curStateId && 36 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 7;
        r_find  = true;
    }
    if (27 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 8;
        r_find  = true;
    }
    if (27 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 8;
        r_find  = true;
    }
    if (27 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 8;
        r_find  = true;
    }
    if (27 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 8;
        r_find  = true;
    }
    if (27 == curStateId && 36 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 8;
        r_find  = true;
    }
    if (28 == curStateId && 30 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 43;
        r_find  = true;
    }
    if (28 == curStateId && 31 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 44;
        r_find  = true;
    }
    if (29 == curStateId && 4 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 19;
        r_find  = true;
    }
    if (29 == curStateId && 15 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 18;
        r_find  = true;
    }
    if (30 == curStateId && 26 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 46;
        r_find  = true;
    }
    if (31 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 29;
        r_find  = true;
    }
    if (31 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 30;
        r_find  = true;
    }
    if (31 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 28;
        r_find  = true;
    }
    if (31 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 31;
        r_find  = true;
    }
    if (32 == curStateId && 10 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 49;
        r_find  = true;
    }
    if (33 == curStateId && 10 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 19;
        r_find  = true;
    }
    if (34 == curStateId && 9 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 50;
        r_find  = true;
    }
    if (35 == curStateId && 9 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 19;
        r_find  = true;
    }
    if (36 == curStateId && 0 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 12;
        r_find  = true;
    }
    if (36 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 12;
        r_find  = true;
    }
    if (36 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 12;
        r_find  = true;
    }
    if (36 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 12;
        r_find  = true;
    }
    if (36 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 12;
        r_find  = true;
    }
    if (37 == curStateId && 15 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 52;
        r_find  = true;
    }
    if (38 == curStateId && 4 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 55;
        r_find  = true;
    }
    if (38 == curStateId && 15 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 54;
        r_find  = true;
    }
    if (39 == curStateId && 27 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 56;
        r_find  = true;
    }
    if (40 == curStateId && 27 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 19;
        r_find  = true;
    }
    if (41 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 2;
        r_find  = true;
    }
    if (41 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 2;
        r_find  = true;
    }
    if (41 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 2;
        r_find  = true;
    }
    if (41 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 2;
        r_find  = true;
    }
    if (41 == curStateId && 36 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 2;
        r_find  = true;
    }
    if (42 == curStateId && 0 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 14;
        r_find  = true;
    }
    if (42 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 14;
        r_find  = true;
    }
    if (42 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 14;
        r_find  = true;
    }
    if (42 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 14;
        r_find  = true;
    }
    if (42 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 14;
        r_find  = true;
    }
    if (43 == curStateId && 15 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 33;
        r_find  = true;
    }
    if (44 == curStateId && 15 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 35;
        r_find  = true;
    }
    if (45 == curStateId && 8 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 38;
        r_find  = true;
    }
    if (45 == curStateId && 9 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 59;
        r_find  = true;
    }
    if (45 == curStateId && 24 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 60;
        r_find  = true;
    }
    if (46 == curStateId && 15 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 40;
        r_find  = true;
    }
    if (47 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 29;
        r_find  = true;
    }
    if (47 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 30;
        r_find  = true;
    }
    if (47 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 28;
        r_find  = true;
    }
    if (47 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 31;
        r_find  = true;
    }
    if (47 == curStateId && 36 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 62;
        r_find  = true;
    }
    if (48 == curStateId && 9 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 63;
        r_find  = true;
    }
    if (49 == curStateId && 15 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 64;
        r_find  = true;
    }
    if (51 == curStateId && 9 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 21;
        r_find  = true;
    }
    if (51 == curStateId && 23 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 69;
        r_find  = true;
    }
    if (52 == curStateId && 9 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 19;
        r_find  = true;
    }
    if (52 == curStateId && 23 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 19;
        r_find  = true;
    }
    if (56 == curStateId && 10 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 71;
        r_find  = true;
    }
    if (57 == curStateId && 10 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 49;
        r_find  = true;
    }
    if (58 == curStateId && 9 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 73;
        r_find  = true;
    }
    if (59 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 12;
        r_find  = true;
    }
    if (59 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 12;
        r_find  = true;
    }
    if (59 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 12;
        r_find  = true;
    }
    if (59 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 12;
        r_find  = true;
    }
    if (59 == curStateId && 36 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 12;
        r_find  = true;
    }
    if (60 == curStateId && 15 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 52;
        r_find  = true;
    }
    if (61 == curStateId && 27 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 75;
        r_find  = true;
    }
    if (62 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 14;
        r_find  = true;
    }
    if (62 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 14;
        r_find  = true;
    }
    if (62 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 14;
        r_find  = true;
    }
    if (62 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 14;
        r_find  = true;
    }
    if (62 == curStateId && 36 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 14;
        r_find  = true;
    }
    if (63 == curStateId && 0 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 9;
        r_find  = true;
    }
    if (63 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 9;
        r_find  = true;
    }
    if (63 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 9;
        r_find  = true;
    }
    if (63 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 9;
        r_find  = true;
    }
    if (63 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 9;
        r_find  = true;
    }
    if (64 == curStateId && 15 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 76;
        r_find  = true;
    }
    if (65 == curStateId && 8 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 78;
        r_find  = true;
    }
    if (65 == curStateId && 11 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 77;
        r_find  = true;
    }
    if (66 == curStateId && 8 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 24;
        r_find  = true;
    }
    if (66 == curStateId && 11 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 24;
        r_find  = true;
    }
    if (67 == curStateId && 0 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 10;
        r_find  = true;
    }
    if (67 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 10;
        r_find  = true;
    }
    if (67 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 10;
        r_find  = true;
    }
    if (67 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 10;
        r_find  = true;
    }
    if (67 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 10;
        r_find  = true;
    }
    if (68 == curStateId && 9 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 79;
        r_find  = true;
    }
    if (69 == curStateId && 9 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 20;
        r_find  = true;
    }
    if (70 == curStateId && 8 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 15;
        r_find  = true;
    }
    if (70 == curStateId && 9 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 15;
        r_find  = true;
    }
    if (70 == curStateId && 24 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 15;
        r_find  = true;
    }
    if (71 == curStateId && 4 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 83;
        r_find  = true;
    }
    if (71 == curStateId && 15 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 82;
        r_find  = true;
    }
    if (72 == curStateId && 9 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 84;
        r_find  = true;
    }
    if (74 == curStateId && 9 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 21;
        r_find  = true;
    }
    if (74 == curStateId && 23 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 69;
        r_find  = true;
    }
    if (75 == curStateId && 10 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 87;
        r_find  = true;
    }
    if (76 == curStateId && 8 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 25;
        r_find  = true;
    }
    if (76 == curStateId && 11 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 25;
        r_find  = true;
    }
    if (77 == curStateId && 9 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 22;
        r_find  = true;
    }
    if (78 == curStateId && 15 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 64;
        r_find  = true;
    }
    if (79 == curStateId && 0 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 11;
        r_find  = true;
    }
    if (79 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 11;
        r_find  = true;
    }
    if (79 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 11;
        r_find  = true;
    }
    if (79 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 11;
        r_find  = true;
    }
    if (79 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 11;
        r_find  = true;
    }
    if (80 == curStateId && 8 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 90;
        r_find  = true;
    }
    if (80 == curStateId && 11 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 89;
        r_find  = true;
    }
    if (81 == curStateId && 8 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 16;
        r_find  = true;
    }
    if (81 == curStateId && 11 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 16;
        r_find  = true;
    }
    if (82 == curStateId && 8 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 17;
        r_find  = true;
    }
    if (82 == curStateId && 11 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 17;
        r_find  = true;
    }
    if (83 == curStateId && 8 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 18;
        r_find  = true;
    }
    if (83 == curStateId && 11 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 18;
        r_find  = true;
    }
    if (84 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 9;
        r_find  = true;
    }
    if (84 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 9;
        r_find  = true;
    }
    if (84 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 9;
        r_find  = true;
    }
    if (84 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 9;
        r_find  = true;
    }
    if (84 == curStateId && 36 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 9;
        r_find  = true;
    }
    if (85 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 10;
        r_find  = true;
    }
    if (85 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 10;
        r_find  = true;
    }
    if (85 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 10;
        r_find  = true;
    }
    if (85 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 10;
        r_find  = true;
    }
    if (85 == curStateId && 36 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 10;
        r_find  = true;
    }
    if (86 == curStateId && 9 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 91;
        r_find  = true;
    }
    if (87 == curStateId && 4 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 83;
        r_find  = true;
    }
    if (87 == curStateId && 15 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 82;
        r_find  = true;
    }
    if (88 == curStateId && 8 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 23;
        r_find  = true;
    }
    if (88 == curStateId && 11 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 23;
        r_find  = true;
    }
    if (89 == curStateId && 9 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 93;
        r_find  = true;
    }
    if (90 == curStateId && 4 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 55;
        r_find  = true;
    }
    if (90 == curStateId && 15 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 54;
        r_find  = true;
    }
    if (91 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 11;
        r_find  = true;
    }
    if (91 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 11;
        r_find  = true;
    }
    if (91 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 11;
        r_find  = true;
    }
    if (91 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 11;
        r_find  = true;
    }
    if (91 == curStateId && 36 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 11;
        r_find  = true;
    }
    if (92 == curStateId && 8 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 90;
        r_find  = true;
    }
    if (92 == curStateId && 11 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 95;
        r_find  = true;
    }
    if (95 == curStateId && 9 == token->tok) {
        r_acc   = 0;
        r_state = 1;
        r_id    = 98;
        r_find  = true;
    }
    if (96 == curStateId && 0 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 13;
        r_find  = true;
    }
    if (96 == curStateId && 22 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 13;
        r_find  = true;
    }
    if (96 == curStateId && 25 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 13;
        r_find  = true;
    }
    if (96 == curStateId && 28 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 13;
        r_find  = true;
    }
    if (96 == curStateId && 34 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 13;
        r_find  = true;
    }
    if (97 == curStateId && 8 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 15;
        r_find  = true;
    }
    if (97 == curStateId && 11 == token->tok) {
        r_acc   = 0;
        r_state = 0;
        r_id    = 15;
        r_find  = true;
    }
    if (r_find == true) {

        if (r_acc == true) {
            *acc = true;
            return true;
        }

        if (r_state == true) {
            states.push(r_id);
            syms.push(new NodeData(token));
            input.pop();
            return true;
        } else {
            return reduce(states, syms, r_state, r_id);
        }
    }
    return false;
}
bool
reduce(std::stack<int>& states, std::stack<Node>& syms, bool r_state, int r_id) {
    if (!r_state) {
        int child_num{ 0 };
        int rule_left_id{ 0 };
        std::vector<Node> child;
        if (r_id == 0) {
            child_num    = 1;
            rule_left_id = 0;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0]); }
            syms.push(node);
        }
        if (r_id == 1) {
            child_num    = 1;
            rule_left_id = 1;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0]); }
            syms.push(node);
        }
        if (r_id == 2) {
            child_num    = 2;
            rule_left_id = 2;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0], child[1]); }
            syms.push(node);
        }
        if (r_id == 3) {
            child_num    = 1;
            rule_left_id = 2;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0]); }
            syms.push(node);
        }
        if (r_id == 4) {
            child_num    = 1;
            rule_left_id = 3;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0]); }
            syms.push(node);
        }
        if (r_id == 5) {
            child_num    = 1;
            rule_left_id = 3;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0]); }
            syms.push(node);
        }
        if (r_id == 6) {
            child_num    = 1;
            rule_left_id = 3;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0]); }
            syms.push(node);
        }
        if (r_id == 7) {
            child_num    = 1;
            rule_left_id = 3;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0]); }
            syms.push(node);
        }
        if (r_id == 8) {
            child_num    = 1;
            rule_left_id = 3;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0]); }
            syms.push(node);
        }
        if (r_id == 9) {
            child_num    = 5;
            rule_left_id = 5;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0], child[1], child[2], child[3], child[4]); }
            syms.push(node);
        }
        if (r_id == 10) {
            child_num    = 5;
            rule_left_id = 6;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0], child[1], child[2], child[3]); }
            syms.push(node);
        }
        if (r_id == 11) {
            child_num    = 6;
            rule_left_id = 4;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0], child[1], child[2], child[3], child[4], child[5]); }
            syms.push(node);
        }
        if (r_id == 12) {
            child_num    = 3;
            rule_left_id = 4;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0], child[1], child[2]); }
            syms.push(node);
        }
        if (r_id == 13) {
            child_num    = 9;
            rule_left_id = 7;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0], child[1], child[2], child[3], child[4], child[5], child[6], child[7]); }
            syms.push(node);
        }
        if (r_id == 14) {
            child_num    = 3;
            rule_left_id = 8;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0], child[1], child[2]); }
            syms.push(node);
        }
        if (r_id == 15) {
            child_num    = 4;
            rule_left_id = 17;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0], child[1], child[2]); }
            syms.push(node);
        }
        if (r_id == 16) {
            child_num    = 1;
            rule_left_id = 17;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0]); }
            syms.push(node);
        }
        if (r_id == 17) {
            child_num    = 1;
            rule_left_id = 28;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0]); }
            syms.push(node);
        }
        if (r_id == 18) {
            child_num    = 1;
            rule_left_id = 28;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0]); }
            syms.push(node);
        }
        if (r_id == 19) {
            child_num    = 1;
            rule_left_id = 11;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0]); }
            syms.push(node);
        }
        if (r_id == 20) {
            child_num    = 1;
            rule_left_id = 19;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0]); }
            syms.push(node);
        }
        if (r_id == 21) {
            child_num    = 0;
            rule_left_id = 19;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            {}
            syms.push(node);
        }
        if (r_id == 22) {
            child_num    = 3;
            rule_left_id = 12;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0], child[1], child[2]); }
            syms.push(node);
        }
        if (r_id == 23) {
            child_num    = 3;
            rule_left_id = 32;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0], child[1], child[2]); }
            syms.push(node);
        }
        if (r_id == 24) {
            child_num    = 1;
            rule_left_id = 32;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0]); }
            syms.push(node);
        }
        if (r_id == 25) {
            child_num    = 2;
            rule_left_id = 33;
            for (int i{ 0 }; i < child_num; i++) {
                child.push_back(syms.top());
                syms.pop();
                states.pop();
            }

            Node node = nullptr;
            // block
            { node = gogo(child[0], child[1]); }
            syms.push(node);
        }

        int curStateId = states.top();
        int nextStateId{ 0 };
        if (0 == curStateId && 1 == rule_left_id) {
            nextStateId = 1;
        }
        if (0 == curStateId && 2 == rule_left_id) {
            nextStateId = 2;
        }
        if (0 == curStateId && 3 == rule_left_id) {
            nextStateId = 3;
        }
        if (0 == curStateId && 4 == rule_left_id) {
            nextStateId = 4;
        }
        if (0 == curStateId && 5 == rule_left_id) {
            nextStateId = 5;
        }
        if (0 == curStateId && 6 == rule_left_id) {
            nextStateId = 6;
        }
        if (0 == curStateId && 7 == rule_left_id) {
            nextStateId = 7;
        }
        if (0 == curStateId && 8 == rule_left_id) {
            nextStateId = 8;
        }
        if (2 == curStateId && 3 == rule_left_id) {
            nextStateId = 13;
        }
        if (2 == curStateId && 4 == rule_left_id) {
            nextStateId = 4;
        }
        if (2 == curStateId && 5 == rule_left_id) {
            nextStateId = 5;
        }
        if (2 == curStateId && 6 == rule_left_id) {
            nextStateId = 6;
        }
        if (2 == curStateId && 7 == rule_left_id) {
            nextStateId = 7;
        }
        if (2 == curStateId && 8 == rule_left_id) {
            nextStateId = 8;
        }
        if (10 == curStateId && 17 == rule_left_id) {
            nextStateId = 16;
        }
        if (10 == curStateId && 28 == rule_left_id) {
            nextStateId = 17;
        }
        if (12 == curStateId && 2 == rule_left_id) {
            nextStateId = 21;
        }
        if (12 == curStateId && 3 == rule_left_id) {
            nextStateId = 22;
        }
        if (12 == curStateId && 4 == rule_left_id) {
            nextStateId = 23;
        }
        if (12 == curStateId && 5 == rule_left_id) {
            nextStateId = 24;
        }
        if (12 == curStateId && 6 == rule_left_id) {
            nextStateId = 25;
        }
        if (12 == curStateId && 7 == rule_left_id) {
            nextStateId = 26;
        }
        if (12 == curStateId && 8 == rule_left_id) {
            nextStateId = 27;
        }
        if (14 == curStateId && 11 == rule_left_id) {
            nextStateId = 32;
        }
        if (15 == curStateId && 11 == rule_left_id) {
            nextStateId = 34;
        }
        if (20 == curStateId && 11 == rule_left_id) {
            nextStateId = 39;
        }
        if (21 == curStateId && 3 == rule_left_id) {
            nextStateId = 41;
        }
        if (21 == curStateId && 4 == rule_left_id) {
            nextStateId = 23;
        }
        if (21 == curStateId && 5 == rule_left_id) {
            nextStateId = 24;
        }
        if (21 == curStateId && 6 == rule_left_id) {
            nextStateId = 25;
        }
        if (21 == curStateId && 7 == rule_left_id) {
            nextStateId = 26;
        }
        if (21 == curStateId && 8 == rule_left_id) {
            nextStateId = 27;
        }
        if (29 == curStateId && 17 == rule_left_id) {
            nextStateId = 45;
        }
        if (29 == curStateId && 28 == rule_left_id) {
            nextStateId = 17;
        }
        if (31 == curStateId && 2 == rule_left_id) {
            nextStateId = 47;
        }
        if (31 == curStateId && 3 == rule_left_id) {
            nextStateId = 22;
        }
        if (31 == curStateId && 4 == rule_left_id) {
            nextStateId = 23;
        }
        if (31 == curStateId && 5 == rule_left_id) {
            nextStateId = 24;
        }
        if (31 == curStateId && 6 == rule_left_id) {
            nextStateId = 25;
        }
        if (31 == curStateId && 7 == rule_left_id) {
            nextStateId = 26;
        }
        if (31 == curStateId && 8 == rule_left_id) {
            nextStateId = 27;
        }
        if (32 == curStateId && 12 == rule_left_id) {
            nextStateId = 48;
        }
        if (37 == curStateId && 11 == rule_left_id) {
            nextStateId = 51;
        }
        if (38 == curStateId && 28 == rule_left_id) {
            nextStateId = 53;
        }
        if (43 == curStateId && 11 == rule_left_id) {
            nextStateId = 57;
        }
        if (44 == curStateId && 11 == rule_left_id) {
            nextStateId = 58;
        }
        if (46 == curStateId && 11 == rule_left_id) {
            nextStateId = 61;
        }
        if (47 == curStateId && 3 == rule_left_id) {
            nextStateId = 41;
        }
        if (47 == curStateId && 4 == rule_left_id) {
            nextStateId = 23;
        }
        if (47 == curStateId && 5 == rule_left_id) {
            nextStateId = 24;
        }
        if (47 == curStateId && 6 == rule_left_id) {
            nextStateId = 25;
        }
        if (47 == curStateId && 7 == rule_left_id) {
            nextStateId = 26;
        }
        if (47 == curStateId && 8 == rule_left_id) {
            nextStateId = 27;
        }
        if (49 == curStateId && 32 == rule_left_id) {
            nextStateId = 65;
        }
        if (49 == curStateId && 33 == rule_left_id) {
            nextStateId = 66;
        }
        if (50 == curStateId && 15 == rule_left_id) {
            nextStateId = 67;
        }
        if (51 == curStateId && 19 == rule_left_id) {
            nextStateId = 68;
        }
        if (53 == curStateId && 15 == rule_left_id) {
            nextStateId = 70;
        }
        if (57 == curStateId && 12 == rule_left_id) {
            nextStateId = 72;
        }
        if (60 == curStateId && 11 == rule_left_id) {
            nextStateId = 74;
        }
        if (71 == curStateId && 17 == rule_left_id) {
            nextStateId = 80;
        }
        if (71 == curStateId && 28 == rule_left_id) {
            nextStateId = 81;
        }
        if (73 == curStateId && 15 == rule_left_id) {
            nextStateId = 85;
        }
        if (74 == curStateId && 19 == rule_left_id) {
            nextStateId = 86;
        }
        if (78 == curStateId && 33 == rule_left_id) {
            nextStateId = 88;
        }
        if (87 == curStateId && 17 == rule_left_id) {
            nextStateId = 92;
        }
        if (87 == curStateId && 28 == rule_left_id) {
            nextStateId = 81;
        }
        if (90 == curStateId && 28 == rule_left_id) {
            nextStateId = 94;
        }
        if (93 == curStateId && 15 == rule_left_id) {
            nextStateId = 96;
        }
        if (94 == curStateId && 15 == rule_left_id) {
            nextStateId = 97;
        }
        if (98 == curStateId && 15 == rule_left_id) {
            nextStateId = 99;
        }
        states.push(nextStateId);
        return true;
    }
    return false;
}
#endif
