#ifndef _c_tab_hpp_
#define _c_tab_hpp_

    #include <iostream>
    #include <stack>
    #include <vector>
    #include <cstring>
    #include "TokenKinds.hpp"
    #include "sema.hpp"
    using namespace std;
union Item {
 
    Node node;
    std::vector<Node>* list;
};

Node yyparse(const char* str);


Node makeLex(Node codeNode, Node unionNode, std::vector<Node>* tokens, std::vector<Node>* types,
                    std::vector<Node>* rules, Node other);

Node makeToken(Node token);

Node makeRule(Node n, std::vector<Node>* l, Node m);

Node makeRule(Node n, std::vector<Node>* l);

Node makeType(Node typeNode, std::vector<Node>* nodes);

Node makeCode(Node block);

Node makeUnion(Node block);

#endif
