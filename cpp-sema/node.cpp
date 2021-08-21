#include "node.hpp"
#include "rule.hpp"
#include "symtab.hpp"
#include "sema.hpp"

NodeData::NodeData() {
    _token = nullptr;
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
    return codeNode;
}

std::string
LexNode::GetUnion() {
    return unionNode;
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

std::vector<Rule>
LexNode::GetRules() {
    std::vector<Rule> g;
    int i{ 0 };
    for (Node n : *rules) {
        RuleNode* rn              = dynamic_cast<RuleNode*>(n);
        Node left                 = rn->left;
        std::vector<Node>* rights = rn->right;
        Rule rule                 = new RuleData();
        rule->id                  = i++;
        rule->funcBlock           = rn->block;
        // left node
        Symbol l_sym = Symtab::SymbolNew(left->GetToken()->value);
        l_sym->clazz = SymbolClass::nterm;

        rule->left = l_sym->id;
        // right nodes
        for (Node r_node : *rights) {
            Symbol r_sym = Symtab::SymbolNew(r_node->GetToken()->value);
            if (r_sym->clazz == none) {
                r_sym->clazz = nterm;
            }

            rule->right.push_back(r_sym);
        }
        g.push_back(rule);
    }
    return g;
}
