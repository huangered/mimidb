#ifndef _reader_hpp_
#define _reader_hpp_

#include "rule.hpp"

class RuleResult {
public:
    std::vector<SimpleRule> rules;
    std::map<std::string, std::string> typeMap;
};

RuleResult ReadRules(const char* path);

FILE* OpenFile(const char* file, const char* mode);
char* ReadFile(FILE* f);
void WriteFile(FILE* f, const char* buf);
void CloseFile(FILE* f);


#endif // !_rule_reader_hpp_
