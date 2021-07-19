#include "sema/rulereader.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>

static std::vector<std::string> split(std::string line);

RuleList
readRules(const char* path) {
    std::map<std::string, SemaToken> semaTokens;
    std::set<std::string> lexTokens;
    std::ifstream file(path);
    std::string myText;

    while (getline(file, myText)) {

        if (myText.starts_with('@')) {
            // handle @token
            myText = myText.substr(7);
            lexTokens.insert(myText);
            continue;
        }

        if (myText.empty()) {
            continue;
        }

        std::vector<std::string> lines = split(myText);

        std::string left = lines[0];

        for (int i{ 2 }; i < lines.size(); i++) {
        }
    }
    return {};
}

std::vector<std::string>
split(std::string line) {
    std::vector<std::string> lines;

    std::string delimiter = " ";

    size_t pos = 0;
    std::string token;
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        lines.push_back(token);
        line.erase(0, pos + delimiter.length());
    }

    return lines;
}