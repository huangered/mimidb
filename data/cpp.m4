include(`value.m4')

#include "c.tab.hpp"
#include <cstring>
#include <cstdlib>

#define MAX_ID 65536

const int goto_table[ NUMSTATE ][ NUMNTERM ] = { DATA_GOTO };
const int action_table[ NUMSTATE ][ NUMTOKEN ] = { DATA_ACTION };
const int rule_right_children_num_arr[] = { DATA_RIGHT_NUM };
const int rule_left_id_arr[] = { DATA_LEFT_ID };

Parser::Parser(yylexer* lexer){
    this->lexer = lexer;
}

Parser::~Parser() {
    delete lexer;
}

YYSTYPE Parser::yylval;

DATA_RETURN
Parser::parse() {

    int t;
    std::vector<InputToken*> data;
    while ((t = lexer->yylex()) != -1) {
        data.push_back(new InputToken{ t, yylval });
        memset(&yylval, 0, sizeof(YYSTYPE));
    }

    InputToken* end = new InputToken{};
    end->tok        = DATA_EOF_ID;
    data.push_back(end);

    YYSTYPE item{};
    std::stack<int> state_stack;
    std::stack<YYSTYPE> token_stack;
    std::stack<InputToken*> input_stack;

    state_stack.push(0);

    for (auto iter = data.rbegin(); iter != data.rend(); iter++) {
        input_stack.push(*iter);
    }

    bool acc{};
    while (!acc) {
        bool op = yyshift(state_stack, token_stack, input_stack, &acc);

        if (!op) {
            printf("no action\n");
            break;
        }
    }
    if (acc) {
        item = token_stack.top();
    } else {
        return nullptr;
    }
    DATA_RETURN* ptr = reinterpret_cast<DATA_RETURN*>(&item);
    return *ptr;
}


bool
Parser::yyshift(std::stack<int>& states, std::stack<YYSTYPE>& syms, std::stack<InputToken*>& input, bool* acc) {
    int curStateId    = states.top();
    InputToken* token = input.top();

    int rd  = action_table[curStateId][token->tok];
    *acc   = (rd == 10000);
    bool r_state = (rd > 0);
    int r_id    = abs( rd );
    bool r_find  = (r_id != MAX_ID);
    if (r_find) {

        if (*acc) {
            return true;
        }

        if (r_state) {
            states.push(r_id);
            YYSTYPE it = token->item;
            syms.push(it);
            input.pop();
            return true;
        } else {
            return yyreduce(states, syms, r_id);
        }
    }
    return false;
}



bool
Parser::yyreduce(std::stack<int>& states, std::stack<YYSTYPE>& syms, int r_id) {
    int child_num{ rule_right_children_num_arr[r_id] };
    int rule_left_id{ rule_left_id_arr[r_id] };
    std::vector<YYSTYPE> child(child_num);
    YYSTYPE item{};
    for (int i{ 0 }; i < child_num; i++) {
        child.insert(child.begin(), syms.top());
        syms.pop();
        states.pop();
    }
    switch (r_id) {
include(`rules.m4')
    }
    syms.push(item);

    int curStateId  = states.top();
    int nextStateId = goto_table[curStateId][rule_left_id - NUMTOKEN];
    states.push(nextStateId);
    return true;
}
