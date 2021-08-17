#ifndef _p_test_hpp_
#define _p_test_hpp_
#include <iostream>
#include <stack>
#include <vector>
#include <cstring>
#include "gogo.hpp"
#include "TokenKinds.hpp"
#include "sema.hpp"
using namespace std;

union Item {
    Node node;
    std::vector<Node>* list;
};
#define MAX_ID 65535
// init goto table (state id, sema id) -> (state id)
const int goto_table[25][24] = {
    {
        MAX_ID, 1,      MAX_ID, MAX_ID, 2,      MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, 4,      MAX_ID, 5,      MAX_ID, MAX_ID, 6,      MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, 9,      MAX_ID, MAX_ID, MAX_ID, 11,     MAX_ID, MAX_ID, MAX_ID, 12,
        13,     MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, 15,
        13,     MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, 17,     MAX_ID,
        18,     MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, 20,     MAX_ID,
        21,     MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        22,     MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        23,     MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
    },
};
// init action table (state id, token id) -> (acc, state, id)
const int action_table[25][21] = {
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, 3,      MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, 7,      MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, -2,     MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, 8,      MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, 10,     MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, -1,     MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, -5,     MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, 14,     MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, -3,     MAX_ID, MAX_ID, MAX_ID,
    },
    {
        10000,  MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, 10,     MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, -13,    MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, -4,     MAX_ID, MAX_ID, MAX_ID,
    },
    {
        -8,     MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, -8,     MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, 16,     MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, 10,     MAX_ID, MAX_ID, MAX_ID,
    },
    {
        -7,     MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, -7,     MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, 19,     MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, 10,     MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, -12,    MAX_ID, MAX_ID, MAX_ID,
    },
    {
        -13,    MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, -13,    MAX_ID, MAX_ID, MAX_ID,
    },
    {
        -10,    MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, 19,     MAX_ID, MAX_ID, MAX_ID,
    },
    {
        -12,    MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, -12,    MAX_ID, MAX_ID, MAX_ID,
    },
    {
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, -11,    MAX_ID, MAX_ID, MAX_ID,
    },
    {
        -11,    MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, -11,    MAX_ID, MAX_ID, MAX_ID,
    },
    {
        -9,     MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID,
        MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, MAX_ID, -9,     MAX_ID, MAX_ID, MAX_ID,
    },
};
const int rule_right_children_num_arr[] = {
    3, 2, 1, 2, 2, 1, 3, 2, 1, 4, 3, 2, 1, 1,
};
const int rule_left_id_arr[] = {
    0, 1, 1, 4, 2, 2, 7, 3, 3, 11, 11, 10, 10, 12,
};
static bool eatToken(std::stack<int>& states, std::stack<Item>& syms, std::stack<LexToken>& input, bool* acc);
static bool reduce(std::stack<int>& states, std::stack<Item>& syms, int r_id);
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

    Item item;
    std::stack<int> state_stack;
    std::stack<Item> token_stack;
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
        item = token_stack.top();
    } else {
        while (!token_stack.empty()) {
            item = token_stack.top();
            token_stack.pop();
            delete item.node;
        }
    }
    return item.node;
}
bool
eatToken(std::stack<int>& states, std::stack<Item>& syms, std::stack<LexToken>& input, bool* acc) {
    int curStateId = states.top();
    LexToken token = input.top();
    bool r_acc;
    bool r_state;
    int r_id;
    bool r_find{ false };
    int rd  = action_table[curStateId][token->tok];
    r_acc   = (rd == 10000);
    r_state = (rd > 0);
    r_id    = rd > 0 ? rd : -rd;
    r_find  = (r_id != MAX_ID);
    if (r_find == true) {

        if (r_acc == true) {
            *acc = true;
            return true;
        }

        if (r_state == true) {
            states.push(r_id);
            Item it;
            it.node = new NodeData(token);
            syms.push(it);
            input.pop();
            return true;
        } else {
            return reduce(states, syms, r_id);
        }
    }
    return false;
}
bool
reduce(std::stack<int>& states, std::stack<Item>& syms, int r_id) {
    int child_num{ rule_right_children_num_arr[r_id] };
    int rule_left_id{ rule_left_id_arr[r_id] };
    std::vector<Item> child(child_num);
    Item item = syms.top();
    for (int i{ 0 }; i < child_num; i++) {
        child.insert(child.begin(), syms.top());
        syms.pop();
        states.pop();
    }
    switch (r_id) {
    case 0:

        // line 14
        // block
        { item.node = makeLex(child[0].list, child[1].list, child[2].list); }
        break;
    case 1:

        // line 16
        // block
        {
            child[0].list->push_back(child[1].node);
            item.list = child[0].list;
        }
        break;
    case 2:

        // line 17
        // block
        {
            std::vector<Node>* vec = new std::vector<Node>();
            vec->push_back(child[0].node);
            item.list = vec;
        }
        break;
    case 3:

        // line 19
        // block
        { item.node = makeToken(child[1].node); }
        break;
    case 4:

        // line 21
        // block
        {
            child[0].list->push_back(child[1].node);
            item.list = child[0].list;
        }
        break;
    case 5:

        // line 22
        // block
        {
            std::vector<Node>* vec = new std::vector<Node>();
            vec->push_back(child[0].node);
            item.list = vec;
        }
        break;
    case 6:

        // line 24
        // block
        { item.node = makeType(child[1].node, child[2].list); }
        break;
    case 7:

        // line 26
        // block
        {
            child[0].list->push_back(child[1].node);
            item.list = child[0].list;
        }
        break;
    case 8:

        // line 27
        // block
        {
            std::vector<Node>* vec = new std::vector<Node>();
            vec->push_back(child[0].node);
            item.list = vec;
        }
        break;
    case 9:

        // line 29
        // block
        { item.node = makeRule(child[0].node, child[2].list, child[3].node); }
        break;
    case 10:

        // line 30
        // block
        { item.node = makeRule(child[0].node, child[2].list); }
        break;
    case 11:

        // line 32
        // block
        {
            child[0].list->push_back(child[1].node);
            item.list = child[0].list;
        }
        break;
    case 12:

        // line 33
        // block
        {
            std::vector<Node>* vec = new std::vector<Node>();
            vec->push_back(child[0].node);
            item.list = vec;
        }
        break;
    case 13:

        // line 35
        // block
        {}
        break;
    }
    syms.push(item);

    int curStateId  = states.top();
    int nextStateId = goto_table[curStateId][rule_left_id];
    states.push(nextStateId);
    return true;
}
#endif
