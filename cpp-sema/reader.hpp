#ifndef _reader_hpp_
#define _reader_hpp_

#include <cstdlib>

FILE* OpenFile(const char* file, const char* mode);
char* ReadFile(FILE* f);
void WriteFile(FILE* f, const char* buf);
void CloseFile(FILE* f);


#endif // !_rule_reader_hpp_
