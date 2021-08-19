#ifndef _gogo_hpp_
#define _gogo_hpp_

#include "debug.hpp"
#include "node.hpp"
#include <vector>
#include "symtab.hpp"

inline Node
makeLex(Node codeNode, Node unionNode, std::vector<Node>* tokens, std::vector<Node>* types, std::vector<Node>* rules) {
    LexNode* n   = new LexNode();
    n->codeNode  = dynamic_cast<CodeNode*>(codeNode);
    n->unionNode = dynamic_cast<UnionNode*>(unionNode);
    n->tokens    = tokens;
    n->types     = types;
    n->rules     = rules;

    return n;
}

inline Node
makeToken(Node token) {
    TokenData* node = new TokenData();
    Symbol sym      = Symtab::SymbolNew(token->GetToken()->name);
    sym->clazz      = SymbolClass::token;
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
makeType(Node typeNode, std::vector<Node>* nodes) {
    TypeData* n1 = new TypeData();
    n1->SetType(typeNode->GetToken()->name);
    n1->SetChildren(nodes);
    return n1;
}

inline Node
makeCode(Node block) {
    CodeNode* codeN = new CodeNode();
    codeN->block    = block;
    return codeN;
}

inline Node
makeUnion(Node block) {
    UnionNode* unionN = new UnionNode();
    unionN->block     = block;
    return unionN;
}

#endif