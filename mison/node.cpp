#include "node.hpp"
#include "rule.hpp"
#include "symtab.hpp"
#include "sema.hpp"

NodeData::NodeData() {
}

NodeData::~NodeData() {
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
        for (std::string n1 : td->_children) {
            _data[n1] = td->_type;
        }
    }
    for (Node n : *tokens){
        TokenData* td = dynamic_cast<TokenData*>(n);
        if (td->_type != "" ) {
            _data[td->_value] = td->_type;
        }
    }
    return _data;
}

std::vector<Rule>
LexNode::GetRules() {
    std::vector<Rule> rList;
    int i{ 0 };
    for (Node n : *rules) {
        RuleNode* rn              = dynamic_cast<RuleNode*>(n);
        Node left                 = rn->left;
        std::vector<Node>* rights = rn->right;
        for (Node right : *rights) {
            RuleRightNode* r = dynamic_cast<RuleRightNode*>(right);
            Rule rule        = new RuleData();
            rule->id         = i++;
            rule->funcBlock  = r->block;
            // left node
            Symbol l_sym = Symtab::SymbolNew(left->_value);
            l_sym->clazz = SymbolClass::nterm;

            rule->left = l_sym;
            rule->root = false;
            // right nodes
            for (Node r_node : *r->right) {
                Symbol r_sym = Symtab::SymbolNew(r_node->_value);
                rule->right.push_back(r_sym);
            }
            rList.push_back(rule);
        }
    }

    // handle start rule
    Rule sRule       = new RuleData();
    sRule->root      = true;
    sRule->id        = i++;
    sRule->funcBlock = "";
    sRule->left      = Symtab::start;
    sRule->right.push_back(Symtab::SymbolNew(startRule));
    rList.push_back(sRule);

    return rList;
}
