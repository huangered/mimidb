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

class Parser {
private:
  union YYSTYPE yylval;
  
public:
  Parser();
  RETURN parse(const char* str);

private:
  bool yyshift(std::stack<int>& states, std::stack<YYSTYPE>& syms, std::stack<InputToken*>& input, bool* acc);
  bool yyreduce(std::stack<int>& states, std::stack<YYSTYPE>& syms, int r_id);
};

CodeBody2


#endif
