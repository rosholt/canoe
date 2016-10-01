%{
#include "heading.h"
#include "ast/add_node.h"
#include "ast/multiply_node.h"
#include "ast/constant_node.h"
#include "ast/function_node.h"

int yyerror(char *s);
int yylex(void);
int yyparse();

int main() {
  return yyparse();
}
%}

%union {
  int            int_val;
  string*        string_ptr;
  Node*          node_ptr;
  FunctionNode*  func_ptr;
}

%token <int_val>    INTEGER_LITERAL
%token <string_ptr> FIELD_NAME

%type <node_ptr> exp
%type <func_ptr> function

%left LEFT_PARENTHESIS
%left RIGHT_PARENTHESIS

%left PLUS
%left MULT
%left DEF
%left END
%left TERMINATOR

%%

input: input input {}
       | function TERMINATOR { $1->BuildIR()->dump(); }
       | function { $1->BuildIR()->dump(); }

function: DEF FIELD_NAME TERMINATOR exp TERMINATOR END {
    FunctionSignature *signature = new FunctionSignature;
    signature->name = $2;
    signature->parameter_array = { new string("a") };
    $$ = new FunctionNode(signature, $4);
  }
/*          | DEF FIELD_NAME LEFT_PARENTHESIS FIELD_NAME RIGHT_PARENTHESIS TERMINATOR exp TERMINATOR END { $$ = new FunctionNode($2, $3, $4); }
*/
exp: INTEGER_LITERAL { $$ = new ConstantNode($1); }
     | exp PLUS exp  { $$ = new AddNode($1, $3); }
     | exp MULT exp  { $$ = new MultiplyNode($1, $3); }
     | FIELD_NAME    { $$ = new ValueNode($1); }
     ;

%%

int yyerror(char *s)
{
  extern char *yytext;
  
  cerr << "ERROR: " << s << " at symbol \"" << yytext << "\"" << endl;
  exit(1);
}
