%{
#include "heading.h"
#include "ast/add_node.h"
#include "ast/multiply_node.h"
#include "ast/constant_node.h"
#include "ast/function_node.h"
#include "llvm/IR/Module.h"
#include "llvm/ADT/STLExtras.h"

int yyerror(char *s);
int yylex(void);
int yyparse();

static LLVMContext TheContext;
static Module *TheModule;

int main() {
  return yyparse();
}
%}

%union {
  int		int_val;
  string*       string_val;
  Node*         node_ptr;
  FunctionNode*         func_ptr;
}

%token	<int_val>	INTEGER_LITERAL
%token	<string_val>	FIELD_NAME
%type	<node_ptr>	exp
%type	<func_ptr>	func
%left	PLUS
%left	MULT
%left	DEF
%left	END

%%

input:		func { $1->BuildIR()->dump(); };

func: DEF FIELD_NAME exp END { $$ = new FunctionNode($2, $3); }

exp:		INTEGER_LITERAL	{ $$ = new ConstantNode($1); }
		| exp PLUS exp	{ $$ = new AddNode($1, $3); }
		| exp MULT exp	{ $$ = new MultiplyNode($1, $3); }
    | FIELD_NAME { $$ = new ValueNode($1); }
		;

%%

int yyerror(char *s)
{
  extern char *yytext;	// defined and maintained in lex.c
  
  cerr << "ERROR: " << s << " at symbol \"" << yytext << "\"" << endl;
  exit(1);
}
