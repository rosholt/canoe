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
  int                 int_val;
  string*             string_ptr;
  Node*               node_ptr;
  FunctionNode*       func_ptr;
  FunctionSignature*  func_signature_ptr;
  vector<Node *>      node_ptr_vector;
}

%token <int_val>    INTEGER_LITERAL
%token <string_ptr> FIELD_NAME

%type <node_ptr> expression
%type <func_ptr> function
%type <func_signature_ptr> function_signature
%type <node_ptr_vector> function_arguments 
%type <node_ptr> function_call 

%left LEFT_PARENTHESIS
%left RIGHT_PARENTHESIS

%left PLUS
%left MULT
%left DEF
%left END
%left TERMINATOR

%%

expressions: expressions expression { $2->BuildIR()->dump(); }
             | expression { $1->BuildIR()->dump(); }

expression: function
            | INTEGER_LITERAL { $$ = new ConstantNode($1); }
            | expression PLUS expression  { $$ = new AddNode($1, $3); }
            | expression MULT expression  { $$ = new MultiplyNode($1, $3); }
            | FIELD_NAME    { $$ = new ValueNode($1); }
            | function_call

function: function_signature TERMINATOR expression TERMINATOR END { $$ = new FunctionNode($1, $3); }

function_signature: DEF FIELD_NAME { $$ = new FunctionSignature; $$->name = $2; }
                    | DEF FIELD_NAME LEFT_PARENTHESIS FIELD_NAME RIGHT_PARENTHESIS {
                        $$ = new FunctionSignature;
                        $$->name = $2;
                        $$->parameter_count = 1;
                        $$->parameter_array = { $4 };
                      }

function_call: FIELD_NAME LEFT_PARENTHESIS function_arguments RIGHT_PARENTHESIS { $$ = new CallNode($1, $3); }

function_arguments: expression function_arguments { $2.push_back($1); $$ = $2; }
                    | expression { $$ = new vector<Node *> {$1}; } 


%%

int yyerror(char *s)
{
  extern char *yytext;
  
  cerr << "ERROR: " << s << " at symbol \"" << yytext << "\"" << endl;
  exit(1);
}
