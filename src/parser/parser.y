%code requires {
#include "parser/tokens.h"
#include "node/parsenode.h"
#include "util/mctx.h"
}
/* simplest version of calculator */
%code {
#include <stdio.h>

void yyerror(YYLTYPE* a, void* b, const char* s);

#define YYMALLOC palloc
#define YYFREE   pfree

}

%locations
%pure_parser
%parse-param {NodeWrap* yyscanner}
%lex-param   {NodeWrap* yyscanner}

%union {
    Node *node;
    char* str;
	List* list;
}

/* declare tokens */
%token EOL
%token CREATE
%token TABLE
%token INSERT
%token INTO
%token VALUES
%token SELECT
%token FROM
%token TEXT
%token UPDATE
%token SET
%type <str> term
%type <str> tbl_name
%type <list> value_list
%type <list> term_list
%type <list> param_list
%type <node> param
%type <node> stmt InsertStmt SelectStmt UpdateStmt CreateTableStmt
%%

stmt: /* nothing */
  InsertStmt
  | SelectStmt
  | UpdateStmt
  | CreateTableStmt
  ;
SelectStmt:
  SELECT value_list FROM tbl_name EOL { yyscanner->node = makeSelectStmt($4, $2); }
  ;
InsertStmt:
  INSERT INTO tbl_name VALUES value_list EOL { yyscanner->node = makeInsertStmt($3, $5); }
  ;
UpdateStmt:
  UPDATE tbl_name SET value_list EOL { yyscanner->node = makeUpdateStmt($2); }
  ;
CreateTableStmt:
  CREATE TABLE tbl_name '(' param_list ')' EOL { yyscanner->node = makeCreateTableStmt($3, $5); }
  ;
tbl_name:
  term { $$ = $1; };

value_list:
  '(' term_list ')' { $$ = $2; }
  ;

term_list: 
   term { List* list = new_list(NT_List); $$ = append_list(list, $1); }
  | term_list ',' term { $$ = append_list($1, $3); }
  ;

param_list:
    param { List* list = new_list(NT_List); $$ = append_list(list, $1); }
  | param_list ',' param { $$ = append_list($1, $3); }
  ;
param:
  term term { $$ = makeParam($1, $2); }
  ;
term: TEXT { }
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

