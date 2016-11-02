%{
#include "heading.h"

int yyerror(char *s);
int yylex(void);
int yyparse();

Scope *scope;
BuilderAdaptor *builder;
ModuleNode *module_node;

int main() {
  scope = new Scope;
  builder = BuilderAdaptor::instance();
  std::string name = "anonymous";
  module_node = new ModuleNode(name);
  return yyparse();
}
%}

%union {
  int                 int_val;
  string*             string_ptr;
  Expression*         expression_ptr;
  Node*               node_ptr;
  FunctionNode*       func_ptr;
  FunctionSignature*  func_signature_ptr;
  SizedNodeArray*     sized_array_ptr;
  ModuleNode*         module_node_ptr;
}

%token <int_val>    INTEGER_LITERAL
%token <string_ptr> FIELD_NAME

%type <expression_ptr> expr
%type <expression_ptr> function
%type <func_signature_ptr> function_signature
%type <sized_array_ptr> function_arguments 
%type <expression_ptr> function_call 
%type <module_node_ptr> exprs 

%left LEFT_PARENTHESIS
%left RIGHT_PARENTHESIS

%left PLUS
%left MULT
%left DEF
%left END
%left TERMINATOR

%%

input: exprs { $1->BuildIR(std::unique_ptr<Scope>(scope), std::unique_ptr<BuilderAdaptor>(builder))->dump(); }

exprs: exprs expr { $$ = $1; $$->append($2); }
             | expr { $$ = module_node; $$->append($1); }

expr: function
            | INTEGER_LITERAL { $$ = new Expression(std::make_unique<ConstantNode>($1)); }
            | expr PLUS expr  { $$ = new Expression(std::make_unique<AddNode>(std::unique_ptr<Expression>($1), std::unique_ptr<Expression>($3))); }
            | expr MULT expr  { $$ = new Expression(std::make_unique<MultiplyNode>(std::unique_ptr<Expression>($1), std::unique_ptr<Expression>($3))); }
            | FIELD_NAME    { $$ = new Expression(std::make_unique<ValueNode>(*$1)); }
            | function_call

function: function_signature TERMINATOR expr TERMINATOR END { $$ = new Expression(std::make_unique<FunctionNode>(std::unique_ptr<FunctionSignature>($1), std::unique_ptr<Expression>($3))); }

function_signature: DEF FIELD_NAME { $$ = new FunctionSignature; $$->name = *$2; }
                    | DEF FIELD_NAME LEFT_PARENTHESIS FIELD_NAME RIGHT_PARENTHESIS {
                        $$ = new FunctionSignature;
                        $$->name = *$2;
                        $$->parameters = vector<std::string> { *$4 };
                      }

function_call: FIELD_NAME LEFT_PARENTHESIS function_arguments RIGHT_PARENTHESIS { std::vector<Expression *> v(std::begin($3->array), std::end($3->array)); $$ = new Expression(std::make_unique<CallNode>(*$1, v)); }

function_arguments: expr function_arguments { $2->push($1); $$ = $2; }
                    | expr { $$ = new SizedArray<Expression *>; $$->push($1); } 


%%

int yyerror(char *s)
{
  extern char *yytext;
  
  cerr << "ERROR: " << s << " at symbol \"" << yytext << "\"" << endl;
  exit(1);
}
