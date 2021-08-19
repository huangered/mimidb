#ifndef _gogo_hpp_
#define _gogo_hpp_

#include "node.hpp"
#include <vector>

Node makeLex(Node codeNode, Node unionNode, std::vector<Node>* tokens, std::vector<Node>* types,
                    std::vector<Node>* rules);

Node makeToken(Node token);

Node makeRule(Node n, std::vector<Node>* l, Node m);

Node makeRule(Node n, std::vector<Node>* l);

Node makeType(Node typeNode, std::vector<Node>* nodes);

Node makeCode(Node block);

Node makeUnion(Node block);

#endif