%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "y.tab.h"

void yyerror(char *);
%}

%%

[0-9]+(\.[0-9]+)?     { yylval.dval = atof(yytext); return NUMBER; }

"sin"                 { return SIN; }
"cos"                 { return COS; }
"tan"                 { return TAN; }
"log"                 { return LOG; }
"ln"                  { return LN; }
"sqrt"                { return SQRT; }
"exp"                 { return EXP; }
"pow"                 { return POW; }
"abs"                 { return ABS; }

"pi"                  { yylval.dval = M_PI; return NUMBER; }
"e"                   { yylval.dval = M_E; return NUMBER; }

"+"                   { return PLUS; }
"-"                   { return MINUS; }
"*"                   { return TIMES; }
"/"                   { return DIVIDE; }
"^"                   { return POWER; }
"%"                   { return MOD; }

"("                   { return LPAREN; }
")"                   { return RPAREN; }
","                   { return COMMA; }

\n                    { return EOL; }
[ \t]                 { /* ignore whitespace */ }
.                     { yyerror("Invalid character"); }

%%

int yywrap(void) {
    return 1;
}
