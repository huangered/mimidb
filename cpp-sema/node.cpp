#include "node.hpp"
#include "rule.hpp"
#include "symtab.hpp"
#include "sema.hpp"

NodeData::NodeData() {
}

NodeData::~NodeData() {
    if (_token != nullptr) {
        delete _token;
    }
}

std::string
NodeData::Name() {
    return _name;
}

void
NodeData::SetToken(LexToken token) {
    _token = token;
}

LexToken
NodeData::GetToken() {
    return _token;
}


std::string
LexNode::GetCode() {
    return codeNode->block->GetToken()->value;
}

std::string
LexNode::GetUnion() {
    return unionNode->block->GetToken()->value;
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
        rule->funcBlock           = rn->block->GetToken()->value;
        // left node
        Symbol l_sym = Symtab::SymbolNew(left->GetToken()->value);
        l_sym->clazz = SymbolClass::nterm;
        rule->left   = new SemaTokenData{ l_sym->id, true, left->GetToken()->value };
        // right nodes
        for (Node r_node : *rights) {
            Symbol r_sym = Symtab::SymbolNew(r_node->GetToken()->value);
            if (r_sym->clazz == none) {
                r_sym->clazz = nterm;
            }
            SemaToken r
                = new SemaTokenData{ r_sym->id, r_sym->clazz == nterm ? true : false, r_node->GetToken()->value };
            rule->right.push_back(r);
        }
        g.push_back(rule);
    }
    return g;
}
