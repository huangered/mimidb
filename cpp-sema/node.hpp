#ifndef _sema_node_hpp_
#define _sema_node_hpp_

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "lexer.hpp"

using std::string;

class NodeData;

typedef NodeData* Node;

class RuleData;

typedef RuleData* Rule;

class NodeData {
    LexToken _token;
    string _name;

public:
    NodeData();

    virtual ~NodeData();

    string Name();
    void SetToken(LexToken token);
    LexToken GetToken();
};

class CodeNode : public NodeData {
public:
    Node block;
};

class UnionNode : public NodeData {
public:
    Node block;
};

class ParamNode : public NodeData {
public:
    std::string param;
};

class TypeData : public NodeData {
public:
    string _type;
    std::vector<string> _children;

public:
    void
    SetType(string type) {
        _type = type;
    }
    void
    SetChildren(std::vector<Node>* nodes) {
        std::for_each(nodes->begin(), nodes->end(), [&](Node n) { _children.push_back(n->GetToken()->value); });
    }
};

class TokenData : public NodeData {};

class LexNode : public NodeData {
public:
    string unionNode;
    string codeNode;
    string param;
    std::vector<Node>* tokens;
    std::vector<Node>* types;
    std::vector<Node>* rules;
    string other;

public:
    string GetCode();

    string GetUnion();

    std::map<string, string> GetTypeMap();

    std::vector<Rule> GetRules();
};

class RuleNode : public NodeData {
public:
    Node left;
    std::vector<Node>* right;
};

class RuleRightNode : public NodeData {
public:
    std::vector<Node>* right;
    string block;
};

#endif
