#ifndef _c_tab_hpp_
#define _c_tab_hpp_

#include <iostream>
#include <stack>
#include <vector>
#include <cstring>

#include "node.hpp"
using namespace std;
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
};
Node yyparse(const char* str);
// code part

Node makeLex(Node codeNode, Node unionNode, std::vector<Node>* tokens, std::vector<Node>* types,
             std::vector<Node>* rules, Node other);

Node makeToken(Node token);

Node makeRule(Node n, std::vector<Node>* l, Node m);

Node makeType(Node typeNode, std::vector<Node>* nodes);

Node makeCode(Node block);

Node makeUnion(Node block);

#endif
