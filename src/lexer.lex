%{
#include "heading.h"
#include "parser.h"

int yyerror(char *s);
%}

/* Primitives */
left_parenthesis     "("
right_parenthesis    ")"
digit                [0-9]
lowercase            [a-z]
uppercase            [A-Z]
symbol               [!@#$%^&_\-=\[\]|\\<>?/]
whitespace           [ \t]+
terminator           [;\n][ \t\n]*

/* Keywords */
def                  "def"
end                  "end"

/* Constants */
integer              {digit}+

/* Field names */
field_start          {lowercase}|{symbol}
field_char           {field_start}|{uppercase}|{digit}
field_name           {field_start}{field_char}*

%%
{left_parenthesis}    return LEFT_PARENTHESIS;
{right_parenthesis}   return RIGHT_PARENTHESIS;

{def}                 return DEF;
{end}                 return END;
{terminator}          return TERMINATOR;

"+"                   return PLUS;
"*"                   return MULT;

{field_name}          { yylval.string_ptr = new string(yytext); return FIELD_NAME; }
{integer}             { yylval.int_val = atoi(yytext); return INTEGER_LITERAL; }

{whitespace}          {}

.                     { std::cerr << "SCANNER "; yyerror(""); exit(1);	}
