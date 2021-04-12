%code requires {
#include "node/tokens.h"
#include "node/parsenode.h"

}
/* simplest version of calculator */
%code {
#include <stdio.h>

void yyerror(YYLTYPE* a, void* b, const char* s);

#define YYMALLOC malloc
#define YYFREE   free

}

%locations
%pure-parser
%parse-param {NodeWrap* yyscanner}
%lex-param   {NodeWrap* yyscanner}

%union {
    Node *node;
    char* str;
    int integer;
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
%token INTEGER
%token UPDATE
%token SET
%token WHERE
%token QUOTE
%token AND
%token EQ
%token IDENT
%token PRIMARY KEY
%type <str> term
%type <str> ident
%type <integer> number
%type <str> tbl_name
%type <list> value_list
%type <list> column_list
%type <list> term_list
%type <list> create_table_param_list
%type <node> create_table_param
%type <node> where_cause
%type <list> where_col_ref_list
%type <node> where_col_ref
%type <list> update_col_ref_list
%type <node> update_col_ref
%type <node> update_param
%type <list> insert_value_list
%type <list> insert_value_list2
%type <node> stmt InsertStmt SelectStmt UpdateStmt CreateTableStmt

%%

stmt: /* nothing */
  InsertStmt
  | SelectStmt
  | UpdateStmt
  | CreateTableStmt
  ;
SelectStmt:
  SELECT column_list FROM tbl_name EOL { yyscanner->node = makeSelectStmt($4, $2); }
  ;
InsertStmt:
  INSERT INTO tbl_name VALUES insert_value_list EOL { yyscanner->node = makeInsertStmt($3, $5); }
  ;
UpdateStmt:
    UPDATE tbl_name SET update_col_ref_list EOL { yyscanner->node = makeUpdateStmt($2, $4, NULL); }
  | UPDATE tbl_name SET update_col_ref_list where_cause EOL { yyscanner->node = makeUpdateStmt($2, $4, $5); }
  ;
update_col_ref_list:
    update_col_ref { List* list = new_list(NT_List); $$ = append_list(list, $1); }
  | update_col_ref_list ',' update_col_ref { $$ = append_list($1, $3); }
  ;
update_col_ref:
  ident EQ update_param { $$ = makeAssignStmt($1, $3); }
  ;
update_param:
    term { $$ = makeStrValue($1); }
  | number { $$ = makeIntValue($1); }
  ;
CreateTableStmt:
  CREATE TABLE tbl_name '(' create_table_param_list ')' EOL { yyscanner->node = makeCreateTableStmt($3, $5); }
  ;
tbl_name:
  ident { $$ = $1; };

value_list:
  '(' term_list ')' { $$ = $2; }
  ;

insert_value_list:
  '(' insert_value_list2 ')' { $$ = $2; }
  ;

insert_value_list2:
    update_param { List* list = new_list(NT_List); $$ = append_list(list, $1); }
  | insert_value_list2 ',' update_param { $$ = append_list($1, $3); }
  ;

column_list: 
    ident { List* list = new_list(NT_List); $$ = append_list(list, $1); }
  | column_list ',' ident { $$ = append_list($1, $3); }
  ;

term_list: 
   term { List* list = new_list(NT_List); $$ = append_list(list, $1); }
  | term_list ',' term { $$ = append_list($1, $3); }
  ;

create_table_param_list:
    create_table_param { List* list = new_list(NT_List); $$ = append_list(list, $1); }
  | create_table_param_list ',' create_table_param { $$ = append_list($1, $3); }
  ;
create_table_param:
    ident ident PRIMARY KEY { $$ = makeColumnDef($1, makeTypeName($2), 1);  }
  | ident ident { $$ = makeColumnDef($1, makeTypeName($2), 0); }
  ;
where_cause:
  WHERE where_col_ref_list { $$ = makeWhereStmt($2); }
  ;
where_col_ref_list:
    where_col_ref { List* list = new_list(NT_List); $$ = append_list(list, $1); }
  | where_col_ref_list AND where_col_ref { $$ = append_list($1, $3); }
  ;
where_col_ref:
  ident EQ term { $$ = makeParam($1, $3); }
  ;

number: INTEGER { }
  ;
ident: IDENT { }
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

