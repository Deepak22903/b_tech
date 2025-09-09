%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
%}

%%

[0-9]+(\.[0-9]+)?    { yylval.num = atof(yytext); return NUMBER; }
"+"                  { return PLUS; }
"-"                  { return MINUS; }
"*"                  { return MULTIPLY; }
"/"                  { return DIVIDE; }
\n                   { return EOL; }  // Define EOL token for end-of-line
[ \t]                ; // Ignore whitespace

%%

int yywrap() {
    return 1;
}
