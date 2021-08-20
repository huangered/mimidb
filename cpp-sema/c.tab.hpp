#ifndef _c_tab_hpp_
#define _c_tab_hpp_

#include <iostream>
#include <stack>
#include <vector>
#include <cstring>

#include "node.hpp"
#include "symtab.hpp"
using namespace std;

#define EndLexToken (new LexTokenData(Symtab::eof->id, "eof"))

union YYSTYPE {

    Node node;
    std::vector<Node>* list;
};

enum yytokentype
{
    whitespace   = 2,
    t_token      = 3,
    t_code       = 4,
    t_colon      = 5,
    t_identifier = 6,
    t_block      = 7,
    t_union      = 8,
    t_type       = 9,
    t_type_type  = 10,
    t_sign       = 11,
    unknown      = 12,
};

Node yyparse(const char* str);

Node makeLex(Node codeNode, Node unionNode, std::vector<Node>* tokens, std::vector<Node>* types,
             std::vector<Node>* rules, Node other);

Node makeToken(Node token);

Node makeRule(Node n, std::vector<Node>* l, Node m);

Node makeType(Node typeNode, std::vector<Node>* nodes);

Node makeCode(Node block);

Node makeUnion(Node block);

#endif
