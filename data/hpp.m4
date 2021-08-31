include(`value.m4')

#ifndef _parser_hpp_
#define _parser_hpp_

#include <stack>

CodeBody

union YYSTYPE {
  UnionBody
};

enum yytokentype {
  TokenBody
};

struct InputToken {
    int tok;
    YYSTYPE item;
};

class yylexer {
public:
  virtual int yylex() = 0;
  virtual ~yylexer() {};
};


class Parser {
public:
  static union YYSTYPE yylval;
private:
  yylexer* lexer;  
public:
  Parser(yylexer* lexer);
  ~Parser();
  DATA_RETURN parse();

private:
  bool yyshift(std::stack<int>& states, std::stack<YYSTYPE>& syms, std::stack<InputToken*>& input, bool* acc);
  bool yyreduce(std::stack<int>& states, std::stack<YYSTYPE>& syms, int r_id);
};

CodeBody2


#endif
