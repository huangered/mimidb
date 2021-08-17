#ifndef _gogo_hpp_
#define _gogo_hpp_
#include "node.hpp"
#include <vector>

inline Node
makeLex(std::vector<Node>* l1, std::vector<Node>* l2, std::vector<Node>* l3) {
    return NULL;
}

inline Node
makeToken(Node node) {
    return node;
}

inline Node
makeRule(Node n, std::vector<Node>* l, Node m) {
    return NULL;
}

inline Node
makeRule(Node n, std::vector<Node>* l) {
    return NULL;
}

inline Node
makeType(Node n, std::vector<Node>* l) {
    return NULL;
}

#endif