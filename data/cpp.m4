include(`value.m4')

#include "c.tab.hpp"

const int goto_table[ ][ ] = {};
const int action_table[][] = {};
const int rule_right_children_num_arr[] = {};
const int rule_left_id_arr[] = {};

Parser::Parser(){
}

RETURN
Parser::parser(const char* str) {
    Lexer lexer(str, strlen(str));
    int t;
    std::vector<InputToken*> data;
    while ((t = lexer.Yylex()) != -1) {
        data.push_back(new InputToken{ t, yylval });
        memset(&yylval, 0, sizeof(YYSTYPE));
    }

    InputToken* end = new InputToken{};
    end->tok        = 1;
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
            std::cout << " no action " << std::endl;
            break;
        }
    }
    if (acc) {
        item = token_stack.top();
    } else {
        return nullptr;
    }
    RETURN* ptr = reinterpret_cast<RETURN>(&item);
    return *ptr;
}


bool
Parser::yyshift(std::stack<int>& states, std::stack<YYSTYPE>& syms, std::stack<InputToken*>& input, bool* acc) {
    int curStateId    = states.top();
    InputToken* token = input.top();
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
    YYSTYPE item = syms.top();
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
    int nextStateId = goto_table[curStateId][rule_left_id - 16];
    states.push(nextStateId);
    return true;
}
