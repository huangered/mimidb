#include "c.tab.hpp"
#include "symtab.hpp"
#include "debug.hpp"

Node
makeLex(Node codeNode, Node unionNode, Node paramNode, std::vector<Node>* tokens, std::vector<Node>* types,
        std::vector<Node>* rules, Node other) {
    LexNode* n   = new LexNode();
    n->codeNode  = dynamic_cast<CodeNode*>(codeNode)->block->GetToken()->value;
    n->unionNode = dynamic_cast<UnionNode*>(unionNode)->block->GetToken()->value;
    n->tokens    = tokens;
    n->types     = types;
    n->param     = dynamic_cast<ParamNode*>(paramNode)->param;
    n->rules     = rules;
    n->other     = other->GetToken()->value;
    return n;
}

Node
makeParam(Node param) {
    ParamNode* node = new ParamNode();
    node->param     = param->GetToken()->value;
    return node;
}

Node
makeToken(Node token) {
    TokenData* node = new TokenData();
    Symbol sym      = Symtab::SymbolNew(token->GetToken()->value);
    sym->clazz      = SymbolClass::token;
    return node;
}

Node
makeRule(Node leftNode, std::vector<Node>* rightList) {
    RuleNode* n1 = new RuleNode();
    n1->left     = leftNode;
    if (rightList == nullptr) {
        n1->right = new std::vector<Node>();
    } else {
        n1->right = rightList;
    }
    return n1;
}


Node
makeRuleRight(std::vector<Node>* rightList, Node blockNode) {
    RuleRightNode* n1 = new RuleRightNode();

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
