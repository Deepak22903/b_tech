%{
#include <stdio.h>
%}

%token NUMBER
%left '+' '-'
%left '*' '/'

%%
calclist: /* empty */
        | calclist exp '\n' { printf("= %d\n", $2); }
        ;

exp: exp '+' exp  { $$ = $1 + $3; }
   | exp '-' exp  { $$ = $1 - $3; }
   | exp '*' exp  { $$ = $1 * $3; }
   | exp '/' exp  { $$ = $1 / $3; }
   | '(' exp ')'  { $$ = $2; }
   | NUMBER       { $$ = $1; }
   ;

%%

int main() {
    yyparse();
    return 0;
}
