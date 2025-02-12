%{
#include "y.tab.h"
%}

%%
[0-9]+  { yylval = atoi(yytext); return NUMBER; }
[-+*/\n] { return yytext[0]; }
[ \t]   ; /* skip whitespace */
.       { return yytext[0]; }
%%

int yywrap() {
    return 1;
}
