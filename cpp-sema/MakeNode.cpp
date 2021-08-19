#include "rev4.hpp"
#include "rule.hpp"
#include "sema.hpp"
#include "symtab.hpp"

Node
makeLex(Node codeNode, Node unionNode, std::vector<Node>* tokens, std::vector<Node>* types, std::vector<Node>* rules, Node other) {
    LexNode* n   = new LexNode();
    n->codeNode  = dynamic_cast<CodeNode*>(codeNode);
    n->unionNode = dynamic_cast<UnionNode*>(unionNode);
    n->tokens    = tokens;
    n->types     = types;
    n->rules     = rules;
    n->other     = other->GetToken()->value;
    return n;
}

Node
makeToken(Node token) {
    TokenData* node = new TokenData();
    Symbol sym      = Symtab::SymbolNew(token->GetToken()->value);
    sym->clazz      = SymbolClass::token;
    return node;
}

Node
makeRule(Node n, std::vector<Node>* l, Node m) {
    RuleNode* n1 = new RuleNode();
    n1->left     = n;
    n1->right    = l;
    n1->block    = m;
    return n1;
}

Node
makeRule(Node n, std::vector<Node>* l) {
    Node n1 = new RuleNode();
    return n1;
}

Node
makeType(Node typeNode, std::vector<Node>* nodes) {
    TypeData* n1 = new TypeData();
    n1->SetType(typeNode->GetToken()->value);
    n1->SetChildren(nodes);
    return n1;
}

Node
makeCode(Node block) {
    CodeNode* codeN = new CodeNode();
    codeN->block    = block;
    return codeN;
}

Node
makeUnion(Node block) {
    UnionNode* unionN = new UnionNode();
    unionN->block     = block;
    return unionN;
}
