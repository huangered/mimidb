#include "gogo.hpp"
#include "rule.hpp"
#include "sema.hpp"

std::map<std::string, std::string>
LexNode::GetTypeMap() {
    std::map<std::string, std::string> _data;
    for each (Node n in* types) {
        TypeData* td = dynamic_cast<TypeData*>(n);
        for each (std::string n in td->_children) {
            _data[n] = td->_type;
        }
    }

    return _data;
}

std::vector<SimpleRule>
LexNode::GetRules() {
    std::vector<SimpleRule> g;
    int i{ 0 };
    for each (Node n in* rules) {
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
        for each (Node r_node in* rights) {
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