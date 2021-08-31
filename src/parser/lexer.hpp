#ifndef _sql_lexer_hpp_
#define _sql_lexer_hpp_

#include "c.tab.hpp"

class SqlLexer : public yylexer {
private:
  int _cur;
  int _size;
  const char* _buf;
  
public:
  SqlLexer(const char* buf, int size);

  int yylex();

private:
  int lexPiont();
  int lexIdentifier();
  int lexBlock();
  int lexSign();
};


#endif
