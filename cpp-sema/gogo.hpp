#ifndef _gogo_hpp_
#define _gogo_hpp_

#include "debug.hpp"
#include "node.hpp"
#include <vector>

inline Node
makeLex(std::vector<Node>* tokens, std::vector<Node>* types, std::vector<Node>* rules) {
    LexNode* n = new LexNode();
    n->tokens  = tokens;
    n->types   = types;
    n->rules   = rules;

    return n;
}

inline Node
makeToken(Node token) {
    TokenData* node = new TokenData();

    return node;
}

inline Node
makeRule(Node n, std::vector<Node>* l, Node m) {
    RuleNode* n1 = new RuleNode();
    n1->left     = n;
    n1->right    = l;
    n1->block    = m;
    return n1;
}

inline Node
makeRule(Node n, std::vector<Node>* l) {
    Node n1 = new RuleNode();
    return n1;
}

inline Node
makeType(Node n, std::vector<Node>* l) {
    Node n1 = new TypeData();
    return n1;
}

#endif