#ifndef _sema_node_hpp_
#define _sema_node_hpp_

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "lexer.hpp"

class NodeData;

typedef NodeData* Node;

class SimpleRuleData;

typedef SimpleRuleData* SimpleRule;

class NodeData {
    LexToken _token;
    std::string _name;

public:
    NodeData();

    virtual ~NodeData();

    std::string Name();
    void SetToken(LexToken token);
    LexToken
    GetToken() {
        return _token;
    }
};

class CodeNode : public NodeData {
public:
    Node block;
};

class UnionNode : public NodeData {
public:
    Node block;
};

class TypeData : public NodeData {
public:
    std::string _type;
    std::vector<std::string> _children;

public:
    void
    SetType(std::string type) {
        _type = type;
    }
    void
    SetChildren(std::vector<Node>* nodes) {
        std::for_each(nodes->begin(), nodes->end(), [&](Node n) { _children.push_back(n->GetToken()->name); });
    }
};

class TokenData : public NodeData {};

class LexNode : public NodeData {
public:
    UnionNode* unionNode;
    CodeNode* codeNode;
    std::vector<Node>* tokens;
    std::vector<Node>* types;
    std::vector<Node>* rules;

public:
    std::string GetCode();

    std::string GetUnion();

    std::map<std::string, std::string> GetTypeMap();

    std::vector<SimpleRule> GetRules();
};

class RuleNode : public NodeData {
public:
    Node left;
    std::vector<Node>* right;
    Node block;
};


#endif