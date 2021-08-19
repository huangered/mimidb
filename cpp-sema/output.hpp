#ifndef _output_hpp_
#define _output_hpp_

#include "sema.hpp"

class Output {
private:
    Parser* parser;
    std::string codeBlock;
    std::string unionBlock;

public:
    Output(Parser* _p);
    void SetCode(std::string b);
    void SetUnion(std::string b);
    void output(const char* filename);

private:
    void writeHeader(FILE* f);
    void writeUnion(FILE* f);
    void writeMatrix(FILE* f);
    void writeMethods(FILE* f);
    void writeLeft(FILE* f);
};

#endif // !_output_hpp_
