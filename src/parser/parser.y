/* simplest version of calculator */
%{
#include <stdio.h>
#include "parser/tokens.h"
extern int yylex();
extern int yyparse();
void yyerror(const char* s);

%}
/* declare tokens */
%token NUMBER
%token ADD SUB MUL DIV ABS
%token EOL
%%
calclist: 
  | calclist exp EOL { printf("= %d %d\n", $1 , $2); } 
  ;
exp: factor { $$ = $1;}
  | exp ADD factor { $$ = $1 + $3; }
  | exp SUB factor { $$ = $1 - $3; }
  ;
factor: term { $$ = $1;}
  | factor MUL term { $$ = $1 * $3; }
  | factor DIV term { $$ = $1 / $3; }
  ;
term: NUMBER { $$ = $1;}
  | ABS term { $$ = $2 >= 0? $2 : - $2; }
  ;
%%
int aaa()
{
  char tstr[] = "1+2+3\n";
  // note yy_scan_buffer is is looking for a double null string
  yy_scan_string(tstr);
  
  int i = yyparse();
  printf("%d", i);
    return 0;
}

void
yyerror(const char *s)
{
    printf("error: %s\n", s);
}
