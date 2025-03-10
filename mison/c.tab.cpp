















#include "c.tab.hpp"
#include <cstring>
#include <cstdlib>

const int MAX_ID = 65535;

const int goto_table[ 56 ][ 17 ] = { 
{2,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,3,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,6,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,9,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,12,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,13,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,17,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,20,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,21,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,25,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,29,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,30,31,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,34,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,35,31,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,38,MAX_ID,39,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,44,MAX_ID,45,46,47,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,48,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,50,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,52,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,44,MAX_ID,45,MAX_ID,55,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
 };
const int action_table[ 56 ][ 17 ] = { 
{MAX_ID,MAX_ID,MAX_ID,1,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,4,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,5,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,10000,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-2,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,7,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,8,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-3,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,10,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,11,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,-1,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,14,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,15,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,11,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,16,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,-5,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-5,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,-6,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-6,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,18,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,19,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,-4,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-4,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,22,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,23,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,19,MAX_ID,24,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-9,MAX_ID,-9,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,26,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,27,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,28,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-8,MAX_ID,-8,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,-7,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-7,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,32,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,-22,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,28,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-25,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,33,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-12,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-12,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-12,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,36,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,37,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,40,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,41,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-11,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-11,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-11,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,42,43,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-19,-19,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-22,MAX_ID,MAX_ID,-22,MAX_ID,-22,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,37,MAX_ID,MAX_ID,-10,MAX_ID,-10,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-21,MAX_ID,MAX_ID,-21,MAX_ID,-21,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-24,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,49,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-22,-22,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-22,-22,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-18,-18,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,42,51,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-17,-17,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-21,-21,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-21,-21,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,53,54,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-15,-15,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-20,MAX_ID,MAX_ID,-20,MAX_ID,-20,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,-23,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,-0,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-16,-16,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-20,-20,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-20,-20,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,42,43,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-19,-19,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-13,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-13,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-13,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-14,-14,MAX_ID,},
 };
const int rule_right_children_num_arr[] = { 11,2,2,2,2,1,2,5,2,1,5,2,1,4,3,1,2,1,1,0,2,1,1,1,2,0,1, };
const int rule_left_id_arr[] = { 25,19,17,18,20,20,26,26,21,21,27,22,22,29,31,31,32,32,32,32,28,28,30,24,23,23,33, };

Parser::Parser(yylexer* lexer){
    this->lexer = lexer;
}

Parser::~Parser() {
    delete lexer;
}

YYSTYPE Parser::yylval;

 Node 
Parser::parse() {

    int t;
    std::vector<InputToken*> data;
    while ((t = lexer->yylex()) != -1) {
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
            printf("no action\n");
            break;
        }
    }
    if (acc) {
        item = token_stack.top();
    } else {
        return nullptr;
    }
     Node * ptr = reinterpret_cast< Node *>(&item);
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
    std::vector<YYSTYPE> child;
    YYSTYPE item{};
    for (int i{ 0 }; i < child_num; i++) {
        child.insert(child.begin(), syms.top());
        syms.pop();
        states.pop();
    }
    switch (r_id) {

    case 0:
        // line 0
        { (item.node) = makeLex((child[0].node), (child[1].node), (child[2].node), (child[3].list), (child[5].list), (child[7].list), (child[8].str), (child[10].node) );  }
        break;
    case 1:
        // line 20
        { (item.node) = makeParam((child[1].node));  }
        break;
    case 2:
        // line 40
        { (item.node) = makeCode((child[1].node));  }
        break;
    case 3:
        // line 60
        { (item.node) = makeUnion((child[1].node));  }
        break;
    case 4:
        // line 80
        { (child[0].list)->push_back((child[1].node)); (item.list) = (child[0].list);  }
        break;
    case 5:
        // line 100
        { std::vector<Node>* vec = new std::vector<Node>(); vec->push_back((child[0].node)); (item.list) = vec;  }
        break;
    case 6:
        // line 120
        { (item.node) = makeToken((child[1].node));  }
        break;
    case 7:
        // line 140
        { (item.node) = makeToken((child[2].node), (child[4].node));  }
        break;
    case 8:
        // line 160
        { (child[0].list)->push_back((child[1].node)); (item.list) = (child[0].list);  }
        break;
    case 9:
        // line 180
        { std::vector<Node>* vec = new std::vector<Node>(); vec->push_back((child[0].node)); (item.list) = vec;  }
        break;
    case 10:
        // line 200
        { (item.node) = makeType((child[2].node), (child[4].list));  }
        break;
    case 11:
        // line 220
        { (child[0].list)->push_back((child[1].node)); (item.list) = (child[0].list);  }
        break;
    case 12:
        // line 240
        { std::vector<Node>* vec = new std::vector<Node>(); vec->push_back((child[0].node)); (item.list) = vec;  }
        break;
    case 13:
        // line 260
        { (item.node) = makeRule((child[0].node), (child[2].list));  }
        break;
    case 14:
        // line 280
        { (child[0].list)->push_back((child[2].node)); (item.list) = (child[0].list);  }
        break;
    case 15:
        // line 300
        { std::vector<Node>* vec = new std::vector<Node>(); vec->push_back((child[0].node)); (item.list) = vec;  }
        break;
    case 16:
        // line 320
        { (item.node) = makeRuleRight((child[0].list), (child[1].node));  }
        break;
    case 17:
        // line 340
        { (item.node) = makeRuleRight((child[0].list), nullptr);  }
        break;
    case 18:
        // line 360
        { (item.node) = makeRuleRight(nullptr, (child[0].node));  }
        break;
    case 19:
        // line 380
        { (item.node) = makeRuleRight(nullptr, nullptr);  }
        break;
    case 20:
        // line 400
        { (child[0].list)->push_back((child[1].node)); (item.list) = (child[0].list);  }
        break;
    case 21:
        // line 420
        { std::vector<Node>* vec = new std::vector<Node>(); vec->push_back((child[0].node)); (item.list) = vec;  }
        break;
    case 22:
        // line 440
        { (item.node) = (child[0].node) ;  }
        break;
    case 23:
        // line 460
        { (item.node) = (child[0].node);  }
        break;
    case 24:
        // line 480
        { (item.str) = makeStartRule((child[1].node));  }
        break;
    case 25:
        // line 500
        {  }
        break;
    case 26:
        // line 520
        {  }
        break;

    }
    syms.push(item);

    int curStateId  = states.top();
    int nextStateId = goto_table[curStateId][rule_left_id - 17];
    states.push(nextStateId);
    return true;
}
