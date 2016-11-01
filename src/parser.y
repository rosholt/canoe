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
  Node*               node_ptr;
  FunctionNode*       func_ptr;
  FunctionSignature*  func_signature_ptr;
  SizedNodeArray*          sized_array_ptr;
  ModuleNode*         module_node_ptr;
}

%token <int_val>    INTEGER_LITERAL
%token <string_ptr> FIELD_NAME

%type <node_ptr> expression
%type <func_ptr> function
%type <func_signature_ptr> function_signature
%type <sized_array_ptr> function_arguments 
%type <node_ptr> function_call 
%type <module_node_ptr> expressions 

%left LEFT_PARENTHESIS
%left RIGHT_PARENTHESIS

%left PLUS
%left MULT
%left DEF
%left END
%left TERMINATOR

%%

input: expressions { module_node->BuildIR(std::unique_ptr<Scope>(scope), std::unique_ptr<BuilderAdaptor>(builder))->dump(); }

expressions: expressions expression { module_node->append($2); std::cout << "2 " << module_node << endl; }
             | expression { module_node->append($1); std::cout << "1 " << module_node << endl; }

expression: function
            | INTEGER_LITERAL { $$ = new ConstantNode($1); }
            | expression PLUS expression  { $$ = new AddNode(std::unique_ptr<Node>($1), std::unique_ptr<Node>($3)); }
            | expression MULT expression  { $$ = new MultiplyNode(std::unique_ptr<Node>($1), std::unique_ptr<Node>($3)); }
            | FIELD_NAME    { $$ = new ValueNode(*$1); }
            | function_call

function: function_signature TERMINATOR expression TERMINATOR END { $$ = new FunctionNode(std::unique_ptr<FunctionSignature>($1), std::unique_ptr<Node>($3)); }

function_signature: DEF FIELD_NAME { $$ = new FunctionSignature; $$->name = *$2; }
                    | DEF FIELD_NAME LEFT_PARENTHESIS FIELD_NAME RIGHT_PARENTHESIS {
                        $$ = new FunctionSignature;
                        $$->name = *$2;
                        $$->parameters = vector<std::string> { *$4 };
                      }

function_call: FIELD_NAME LEFT_PARENTHESIS function_arguments RIGHT_PARENTHESIS { std::vector<Node *> v(std::begin($3->array), std::end($3->array)); $$ = new CallNode(*$1, v); }

function_arguments: expression function_arguments { $2->push($1); $$ = $2; }
                    | expression { $$ = new SizedArray<Node *>; $$->push($1); } 


%%

int yyerror(char *s)
{
  extern char *yytext;
  
  cerr << "ERROR: " << s << " at symbol \"" << yytext << "\"" << endl;
  exit(1);
}
