#ifndef _gogo_hpp_
#define _gogo_hpp_
#include "node.hpp"
#include <vector>

inline Node
makeLex(std::vector<Node>* l1, std::vector<Node>* l2, std::vector<Node>* l3) {
    Node n = new NodeData("lex");
    return n;
}

inline Node
makeToken(Node token) {
    TokenPtr ptr = new TokenData{};
    ptr->name    = token->Name();

    return token;
}

inline Node
makeRule(Node n, std::vector<Node>* l, Node m) {
    Node n1 = new NodeData("rule");
    return n1;
}

inline Node
makeRule(Node n, std::vector<Node>* l) {
    Node n1 = new NodeData("rule");
    return n1;
}

inline Node
makeType(Node n, std::vector<Node>* l) {
    Node n1 = new NodeData("type");
    return n1;
}

#endif