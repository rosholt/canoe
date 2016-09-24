%{
#include "heading.h"
#include "parser.h"

int yyerror(char *s);
%}

digit            [0-9]
lowercase        [a-z]
uppercase        [A-Z]
symbol           [!@#$%^&()_\-=\[\]|\\<>?/]
valid_field_start_char       ({lowercase}|{symbol})
valid_char       ({valid_field_start_char}|{uppercase})

%%
"def"           return DEF;
"end"           return END;
{valid_field_start_char}{valid_char}* { yylval.string_val = new string(yytext); return FIELD_NAME; }
{digit}+		{ yylval.int_val = atoi(yytext); return INTEGER_LITERAL; }
"+"		return PLUS;
"*"		return MULT;

[ \t\n]*	{}

.		{ std::cerr << "SCANNER "; yyerror(""); exit(1);	}
