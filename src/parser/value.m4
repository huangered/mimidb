define(CodeBody, `
#include "node/node.hpp"
#include "node/parsenode.hpp"
#include  <list>
#include <cstdlib>
#include <cstdio>
')
define(UnionBody,`
    Node *node;
    int num;
    char* str;
    std::list<Node*>* list;
')
define(TokenBody, `             CREATE =   2,
              TABLE =   3,
             SELECT =   4,
               FROM =   5,
             UPDATE =   6,
               INTO =   7,
             INSERT =   8,
             DELETE =   9,
                SET =  10,
              WHERE =  11,
            ORDERBY =  12,
              BEGIN =  13,
             COMMIT =  14,
          semicolon =  15,
              comma =  16,
             t_text =  17,
           t_number =  18,
            t_block =  19,
            l_paran =  20,
            r_paran =  21,
               star =  22,
')
define(CodeBody2,`

')
define(NUMNTERM, `19')
define(NUMTOKEN, `23')
define(NUMSTATE, `52')
define(DATA_ACTION, `
{MAX_ID,MAX_ID,1,MAX_ID,2,MAX_ID,3,MAX_ID,4,5,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,12,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,13,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,16,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,-20,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,17,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,-20,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,17,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,10000,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,-3,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,-4,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,-5,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,-6,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,-7,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,20,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-19,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-19,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,21,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,22,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-18,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-18,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,23,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,-11,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,-12,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,26,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,28,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,13,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,-20,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,17,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,-21,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,-23,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,32,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,35,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,36,-20,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-17,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-17,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,-10,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,-22,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,38,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,39,MAX_ID,MAX_ID,MAX_ID,MAX_ID,40,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-15,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-15,MAX_ID,},
{MAX_ID,-8,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,43,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-16,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-16,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,32,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-13,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-21,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-23,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,49,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-14,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-14,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-22,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-24,50,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-26,-26,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,-9,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,-25,-25,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
')
define(DATA_GOTO, `
{MAX_ID,6,MAX_ID,7,8,9,10,11,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,14,MAX_ID,MAX_ID,MAX_ID,MAX_ID,15,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,18,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,19,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,24,25,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,27,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,29,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,30,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,31,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,33,34,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,37,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,41,42,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,44,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,45,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,46,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,47,48,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,51,},
{MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,MAX_ID,},
')
define(DATA_RIGHT_NUM, `1,2,1,1,1,1,1,1,5,7,4,2,2,3,3,1,2,3,1,1,0,2,2,1,2,3,1,')
define(DATA_LEFT_ID, `23,25,25,24,24,24,24,24,26,27,28,29,30,31,35,35,36,32,32,37,33,33,38,38,34,40,40,')
define(DATA_EOF_ID, `1')
define(DATA_RETURN, ` Node* ')
