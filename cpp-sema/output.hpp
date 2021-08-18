#ifndef _output_hpp_
#define _output_hpp_

#include "sema.hpp"

class Output {
    Parser* parser;

public:
    Output(Parser* _p);
    void output(const char* filename);

private:
    void writeHeader();
    void writeUnion();
    void writeMatrix();
    void writeMethods();
    void writeLeft();
};

#endif // !_output_hpp_
