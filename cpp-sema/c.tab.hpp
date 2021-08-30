

#ifndef _parser_hpp_
#define _parser_hpp_

#include <stack>

#include <vector>
#include "node.hpp"

int yylex();

union YYSTYPE {

    Node node;
    std::vector<Node>* list;
    char* str;
};

enum yytokentype
{
    t_token      = 2,
    t_code       = 3,
    t_colon      = 4,
    t_identifier = 5,
    t_block      = 6,
    t_union      = 7,
    t_type       = 8,
    t_type_type  = 9,
    t_sign       = 10,
    t_less       = 11,
    t_greater    = 12,
    t_param      = 13,
    t_maybe      = 14,
    t_semicolon  = 15,
    t_start_rule = 16,
};

struct InputToken {
    int tok;
    YYSTYPE item;
};

class Parser {
public:
    static union YYSTYPE yylval;

public:
    Parser();
    Node parse(const char* str);

private:
    bool yyshift(std::stack<int>& states, std::stack<YYSTYPE>& syms, std::stack<InputToken*>& input, bool* acc);
    bool yyreduce(std::stack<int>& states, std::stack<YYSTYPE>& syms, int r_id);
};

Node makeLex(Node codeNode, Node unionNode, Node paramNode, std::vector<Node>* tokens, std::vector<Node>* types,
             std::vector<Node>* rules, char* startRule, Node other);

Node makeToken(Node token);

Node makeToken(Node typeNode, Node token);

Node makeRule(Node n, std::vector<Node>* l);

Node makeRuleRight(std::vector<Node>* n, Node m);

Node makeType(Node typeNode, std::vector<Node>* nodes);

Node makeCode(Node block);

Node makeUnion(Node block);

Node makeParam(Node param);

char* makeStartRule(Node startRule);

#endif
