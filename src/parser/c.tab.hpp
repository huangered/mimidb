














#ifndef _parser_hpp_
#define _parser_hpp_

#include <stack>


#include "node/node.hpp"
#include "node/parsenode.hpp"
#include  <list>
#include <cstdlib>
#include <cstdio>


union YYSTYPE {
  
    Node* node;
    int num;
    char* str;
    std::list<Node*>* list;

};

enum yytokentype {
               CREATE =   2,
              TABLE =   3,
             SELECT =   4,
               FROM =   5,
             UPDATE =   6,
               INTO =   7,
             INSERT =   8,
             DELETE =   9,
                SET =  10,
              WHERE =  11,
            ORDERBY =  12,
              BEGIN =  13,
             COMMIT =  14,
          semicolon =  15,
              comma =  16,
             t_text =  17,
           t_number =  18,
            t_block =  19,
            l_paran =  20,
            r_paran =  21,
               star =  22,

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
