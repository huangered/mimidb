














#ifndef _parser_hpp_
#define _parser_hpp_

#include <stack>


#include "node/parsenode.hpp"
#include <vector>
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
            PRIMARY =  16,
                KEY =  17,
            FOREIGN =  18,
         REFERENCES =  19,
                NOT =  20,
             T_NULL =  21,
               DROP =  22,
              ALTER =  23,
                AND =  24,
                 OR =  25,
               JOIN =  26,
          semicolon =  27,
              comma =  28,
               t_id =  29,
             t_text =  30,
           t_number =  31,
            t_block =  32,
            l_paran =  33,
            r_paran =  34,
               star =  35,

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
