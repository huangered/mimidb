define(CodeBody, `
#include <vector>
#include "node.hpp"

int yylex();

')
define(UnionBody,` 
    Node node;
    std::vector<Node>* list;
    char* str;
')
define(TokenBody, `            t_token =   2,
             t_code =   3,
            t_colon =   4,
       t_identifier =   5,
            t_block =   6,
            t_union =   7,
             t_type =   8,
        t_type_type =   9,
             t_sign =  10,
             t_less =  11,
          t_greater =  12,
            t_param =  13,
            t_maybe =  14,
        t_semicolon =  15,
       t_start_rule =  16,
')
define(CodeBody2,`

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

')
define(NUMNTERM, `17')
define(NUMTOKEN, `17')
define(NUMSTATE, `56')
define(DATA_ACTION, `
{MAX_ID,MAX_ID,MAX_ID,1,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,4,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,10000,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,5,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-3,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,7,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,8,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-4,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,10,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,11,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,-2,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,14,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,15,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,11,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,16,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,-6,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-6,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,-7,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-7,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,18,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,19,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,-5,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-5,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,22,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,23,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,19,MAX_ID,24,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-10,MAX_ID,-10,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,26,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,27,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,28,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-9,MAX_ID,-9,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,-8,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-8,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,32,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,-23,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,28,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-26,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,33,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-13,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-13,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-13,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,36,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,37,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,40,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,41,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-12,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-12,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-12,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,42,43,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-20,-20,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-23,MAX_ID,MAX_ID,-23,MAX_ID,-23,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,37,MAX_ID,MAX_ID,-11,MAX_ID,-11,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-22,MAX_ID,MAX_ID,-22,MAX_ID,-22,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-25,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,49,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-23,-23,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-23,-23,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-19,-19,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,42,51,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-18,-18,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-22,-22,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-22,-22,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,53,54,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-16,-16,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-21,MAX_ID,MAX_ID,-21,MAX_ID,-21,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,-24,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,-1,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-17,-17,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-21,-21,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-21,-21,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,42,43,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-20,-20,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-14,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-14,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-14,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-15,-15,MAX_ID,},
')
define(DATA_GOTO, `
{MAX_ID,2,3,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,6,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,9,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,12,MAX_ID,MAX_ID,MAX_ID,MAX_ID,13,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,17,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,20,MAX_ID,MAX_ID,MAX_ID,MAX_ID,21,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,25,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,29,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,30,31,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,34,MAX_ID,MAX_ID,MAX_ID,MAX_ID,35,31,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,38,MAX_ID,39,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,44,MAX_ID,45,46,47,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,48,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,50,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,52,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,44,MAX_ID,45,MAX_ID,55,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
')
define(DATA_RIGHT_NUM, `1,11,2,2,2,2,1,2,5,2,1,5,2,1,4,3,1,2,1,1,0,2,1,1,1,2,0,')
define(DATA_LEFT_ID, `17,18,21,19,20,22,22,27,27,23,23,28,24,24,30,32,32,33,33,33,33,29,29,31,26,25,25,')
define(DATA_EOF_ID, `1')
define(DATA_RETURN, ` Node ')