#ifndef _rule_reader_hpp_
#define _rule_reader_hpp_

#include "sema/rule.hpp"

class RuleResult {
public:
    std::vector<SimpleRule> rules;
    std::map<std::string, std::string> typeMap;
};

RuleResult ReadRules(const char* path);

#endif // !_rule_reader_hpp_
