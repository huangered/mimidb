#include "c.tab.hpp"
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
makeRule(Node leftNode, std::vector<Node>* rightList, Node blockNode) {
    RuleNode* n1 = new RuleNode();
    n1->left     = leftNode;
    if (rightList == nullptr) {
        n1->right = new std::vector<Node>();
    } else {
        n1->right = rightList;
    }
    if (blockNode == nullptr) {
        n1->block = "";
    } else {
        n1->block = blockNode->GetToken()->value;
    }
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
