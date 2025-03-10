#include "c.tab.hpp"
#include "symtab.hpp"
#include "debug.hpp"
#include <cstring>

Node
makeLex(Node codeNode, Node unionNode, Node paramNode, std::vector<Node>* tokens, std::vector<Node>* types,
        std::vector<Node>* rules, char* startRule, Node other) {
    LexNode* n   = new LexNode();
    n->codeNode  = dynamic_cast<CodeNode*>(codeNode)->block;
    n->unionNode = dynamic_cast<UnionNode*>(unionNode)->block;
    n->tokens    = tokens;
    n->types     = types;
    n->param     = dynamic_cast<ParamNode*>(paramNode)->param;
    n->rules     = rules;
    n->other     = other->_value;
    n->startRule.assign(startRule, startRule + strlen(startRule));
    delete codeNode;
    delete unionNode;
    delete paramNode;
    delete other;
    return n;
}

Node
makeParam(Node param) {
    ParamNode* node = new ParamNode();
    node->param     = param->_value;
    delete param;
    return node;
}

Node
makeToken(Node token) {
    TokenData* node = new TokenData();
    node->_type = "";
    Symbol sym      = Symtab::SymbolNew(token->_value);
    sym->clazz      = SymbolClass::token;
    delete token;
    return node;
}

Node
makeToken(Node typeNode, Node token) {
    TokenData* node = new TokenData();
    node->_type     = typeNode->_value;
    node->_value    = token->_value;
    Symbol sym      = Symtab::SymbolNew(token->_value);
    sym->clazz      = SymbolClass::token;
    delete token;
    delete typeNode;
    return node;
}

Node
makeRule(Node leftNode, std::vector<Node>* rightList) {
    Symbol sym = Symtab::SymbolNew(leftNode->_value);
    sym->clazz = nterm;

    RuleNode* rule = new RuleNode();
    rule->left     = leftNode;
    if (rightList == nullptr) {
        rule->right = new std::vector<Node>();
    } else {
        rule->right = rightList;
    }

    return rule;
}

Node
makeRuleRight(std::vector<Node>* rightList, Node blockNode) {
    RuleRightNode* n1 = new RuleRightNode();

    if (rightList == nullptr) {
        n1->right = new std::vector<Node>();
    } else {
        n1->right = rightList;
        for (Node n : *n1->right) {
            Symbol sym = Symtab::SymbolNew(n->_value);

            if (sym->clazz == none) {
                sym->clazz = nterm;
            }
        }
    }
    if (blockNode == nullptr) {
        n1->block = "";
    } else {
        n1->block = blockNode->_value;
    }
    delete blockNode;
    return n1;
}

Node
makeType(Node typeNode, std::vector<Node>* nodes) {
    TypeData* n1 = new TypeData();
    n1->SetType(typeNode->_value);
    n1->SetChildren(nodes);
    delete typeNode;
    return n1;
}

Node
makeCode(Node block) {
    CodeNode* codeN = new CodeNode();
    codeN->block    = block->_value;
    delete block;
    return codeN;
}

Node
makeUnion(Node block) {
    UnionNode* unionN = new UnionNode();
    unionN->block     = block->_value;
    delete block;
    return unionN;
}

char*
makeStartRule(Node rule) {
    int len    = rule->_value.size();
    char* data = new char[len];
    strcpy(data, rule->_value.c_str());

    // register $_start nterm
    Symtab::start        = Symtab::SymbolNew("$t_start");
    Symtab::start->clazz = nterm;
    return data;
}
