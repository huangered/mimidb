














#ifndef _parser_hpp_
#define _parser_hpp_

#include <stack>


#include "node/node.hpp"
#include "node/parsenode.hpp"
#include  <vector>
#include <cstdlib>
#include <cstdio>


union YYSTYPE {
  
  Node* node;
  int num;
  char* str;
  std::vector<Node*>* list;

};

enum yytokentype {
               CREATE =   2,
              TABLE =   3,
             SELECT =   4,
               FROM =   5,
             UPDATE =   6,
               INTO =   7,
             INSERT =   8,
             VALUES =   9,
             DELETE =  10,
                SET =  11,
              WHERE =  12,
            ORDERBY =  13,
              BEGIN =  14,
             COMMIT =  15,
          semicolon =  16,
              comma =  17,
             t_text =  18,
           t_number =  19,
            t_block =  20,
            l_paran =  21,
            r_paran =  22,
               star =  23,

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
   Node*  parse();

private:
  bool yyshift(std::stack<int>& states, std::stack<YYSTYPE>& syms, std::stack<InputToken*>& input, bool* acc);
  bool yyreduce(std::stack<int>& states, std::stack<YYSTYPE>& syms, int r_id);
};



Node* mison_parse(const char* str);




#endif
