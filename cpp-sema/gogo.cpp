#include "gogo.hpp"
#include "rule.hpp"
#include "sema.hpp"
#include "symtab.hpp"

Node
makeLex(Node codeNode, Node unionNode, std::vector<Node>* tokens, std::vector<Node>* types, std::vector<Node>* rules) {
    LexNode* n   = new LexNode();
    n->codeNode  = dynamic_cast<CodeNode*>(codeNode);
    n->unionNode = dynamic_cast<UnionNode*>(unionNode);
    n->tokens    = tokens;
    n->types     = types;
    n->rules     = rules;

    return n;
}

Node
makeToken(Node token) {
    TokenData* node = new TokenData();
    Symbol sym      = Symtab::SymbolNew(token->GetToken()->name);
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
    n1->SetType(typeNode->GetToken()->name);
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

std::string
LexNode::GetCode() {
    return codeNode->block->GetToken()->name;
}

std::string
LexNode::GetUnion() {
    return unionNode->block->GetToken()->name;
}

std::map<std::string, std::string>
LexNode::GetTypeMap() {
    std::map<std::string, std::string> _data;
    for (Node n : *types) {
        TypeData* td = dynamic_cast<TypeData*>(n);
        for (std::string n : td->_children) {
            _data[n] = td->_type;
        }
    }

    return _data;
}

std::vector<SimpleRule>
LexNode::GetRules() {
    std::vector<SimpleRule> g;
    int i{ 0 };
    for (Node n : *rules) {
        RuleNode* rn              = dynamic_cast<RuleNode*>(n);
        Node left                 = rn->left;
        std::vector<Node>* rights = rn->right;
        SimpleRule rule           = new SimpleRuleData();
        rule->id                  = i++;
        rule->funcBlock           = rn->block->GetToken()->name;
        // left node
        Symbol l_sym = Symtab::SymbolNew(left->GetToken()->name);
        l_sym->clazz = SymbolClass::nterm;
        rule->left   = new SemaTokenData{ l_sym->id, true, left->GetToken()->name };
        // right nodes
        for (Node r_node : *rights) {
            Symbol r_sym = Symtab::SymbolNew(r_node->GetToken()->name);
            if (r_sym->clazz == none) {
                r_sym->clazz = nterm;
            }
            SemaToken r
                = new SemaTokenData{ r_sym->id, r_sym->clazz == nterm ? true : false, r_node->GetToken()->name };
            rule->right.push_back(r);
        }
        g.push_back(rule);
    }
    return g;
}
