%code requires {
#include "parser/tokens.h"
}
/* simplest version of calculator */
%code {
#include <stdio.h>

void yyerror(YYLTYPE* a, void* b, const char* s);

}

%locations
%pure_parser
%parse-param {NodeWrap* yyscanner}
%lex-param   {NodeWrap* yyscanner}

%union {
    Node *node;
    char* m;
}

/* declare tokens */
%token EOL
%token SELECT
%token FROM
%token TEXT
%type <m> term
%type <node> stmt
%%

stmt: /* nothing */
  | SELECT term FROM term EOL { yyscanner->node = makeSelectStmt($2, $4);}
  ;
term:
  | TEXT {}
  ;
%start stmt;
%%

Node*
raw_parse(const char* str)
{
  // note yy_scan_buffer is is looking for a double null string
  yy_scan_string(str);
  NodeWrap p;

  int i = yyparse(&p);
  if(i == 0) {
    return p.node;
  }
  return NULL;
}

void
yyerror(YYLTYPE* a, void* b, const char *s)
{
    printf("error: %s\n", s);
}

Node*
makeSelectStmt(char* a1, char* a2) {
	printf("makeSelectStmt");
	SelectStmt* stmt = (SelectStmt*)malloc(sizeof(SelectStmt));
	stmt->nodetag = NT_SelectStmt;
	stmt->relname = a2;
	stmt->column = a1;
	return (Node*)stmt;
}
