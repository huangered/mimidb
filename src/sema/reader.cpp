#include "sema/rulereader.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include "sema/sema.hpp"

static std::vector<std::string> split(std::string line);

std::vector<SimpleRule>
ReadRules(const char* path) {
    int sema_id{ 0 };
    std::vector<SimpleRule> rList;
    std::map<std::string, int> semaTokens;
    std::map<std::string, int> lexTokens;
    std::ifstream file(path);
    std::string myText;
    int rule_id{ 0 };
    while (getline(file, myText)) {

        if (myText.find('@') == 0) {
            // handle @token
            myText = myText.substr(7);
            Tok t  = GetTokByName(myText);

            lexTokens[myText] = t;

            continue;
        }

        if (myText.empty()) {
            continue;
        }

        std::vector<std::string> lines = split(myText);

        SemaToken l_token;
        SemaTokenList r_token;

        std::string l_name = lines[0];

        if (semaTokens.count(l_name) == 0) {
            semaTokens[l_name] = sema_id;
            sema_id++;
        }

        l_token = new SemaTokenData {semaTokens[l_name], true, l_name};

        for (int i{ 2 }; i < lines.size(); i++) {

            if (lines[i].find('{') == 0) {
                break;
            }

            std::string name = lines[i];
            bool terminal{ false };
            // 如果是 终止符号
            if (lexTokens.count(name) != 0) {
                terminal = true;
            }

            if (semaTokens.count(name) == 0) {
                semaTokens[name] = sema_id;
                sema_id++;
            }

            r_token.push_back(new SemaTokenData{ semaTokens[name], !terminal, name });
        }

        SimpleRule sRule = make_rule(rule_id, l_token, r_token);
        rList.push_back(sRule);
        rule_id++;
    }
    return rList;
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