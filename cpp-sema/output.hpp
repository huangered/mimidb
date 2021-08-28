#ifndef _output_hpp_
#define _output_hpp_

#include "sema.hpp"

class Output {
private:
    SemaParser* parser;
    std::string codeBlock;
    std::string unionBlock;
    std::string other;
    std::string param;

public:
    Output(SemaParser* _p);
    void SetCode(std::string b);
    void SetUnion(std::string b);
    void SetOther(std::string other);
    void SetParam(std::string param);
    void OutputFile(const char* fout);

private:
    void writeCode(FILE* f);
    void writeUnion(FILE* f);
    void writeTokEnum(FILE* f);
    void writeOther(FILE* f);
    void writeM4(const char* fout);
    void writeRule(FILE* f);
    void writeConst(FILE* f);
};

#endif // !_output_hpp_
