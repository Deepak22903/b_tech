%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void yyerror(const char *s);
int yylex(void);

%}

%token <num> NUMBER
%token PLUS MINUS MULTIPLY DIVIDE LPAREN RPAREN EOL // Include EOL token
%type <num> expr term factor

%union {
    double num;
}

%%

input:  /* empty */
    | input expr EOL { printf("Result = %lf\n", $2); }
    ;

expr:   term
    |   expr PLUS term    { $$ = $1 + $3; }
    |   expr MINUS term   { $$ = $1 - $3; }
    ;

term:   factor
    |   term MULTIPLY factor  { $$ = $1 * $3; }
    |   term DIVIDE factor    { $$ = $1 / $3; }
    ;

factor: NUMBER;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    yyparse();
    return 0;
}
