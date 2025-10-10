%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void yyerror(char *);
int yylex(void);
%}

%union {
    double dval;
}

%token <dval> NUMBER
%token SIN COS TAN LOG LN SQRT EXP POW ABS
%token PLUS MINUS TIMES DIVIDE POWER MOD
%token LPAREN RPAREN COMMA EOL

%type <dval> expression term factor power unary primary

%%

program:
    /* empty */
    | program line
    ;

line:
    EOL
    | expression EOL { printf("Result: %.10g\n", $1); }
    | error EOL { yyerrok; }
    ;

/* UNAMBIGUOUS GRAMMAR - explicit precedence in grammar rules */
expression:
    term                        { $$ = $1; }
    | expression PLUS term      { $$ = $1 + $3; }
    | expression MINUS term     { $$ = $1 - $3; }
    ;

term:
    factor                      { $$ = $1; }
    | term TIMES factor         { $$ = $1 * $3; }
    | term DIVIDE factor        { 
        if ($3 == 0) {
            yyerror("Division by zero");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
    }
    | term MOD factor           { $$ = fmod($1, $3); }
    ;

factor:
    power                       { $$ = $1; }
    ;

power:
    unary                       { $$ = $1; }
    | unary POWER power         { $$ = pow($1, $3); }
    ;

unary:
    primary                     { $$ = $1; }
    | MINUS unary               { $$ = -$2; }
    | PLUS unary                { $$ = $2; }
    ;

primary:
    NUMBER                                  { $$ = $1; }
    | LPAREN expression RPAREN              { $$ = $2; }
    | SIN LPAREN expression RPAREN          { $$ = sin($3); }
    | COS LPAREN expression RPAREN          { $$ = cos($3); }
    | TAN LPAREN expression RPAREN          { $$ = tan($3); }
    | LOG LPAREN expression RPAREN          { $$ = log10($3); }
    | LN LPAREN expression RPAREN           { $$ = log($3); }
    | SQRT LPAREN expression RPAREN         { $$ = sqrt($3); }
    | EXP LPAREN expression RPAREN          { $$ = exp($3); }
    | ABS LPAREN expression RPAREN          { $$ = fabs($3); }
    | POW LPAREN expression COMMA expression RPAREN { $$ = pow($3, $5); }
    ;

%%

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Scientific Calculator (Unambiguous Grammar)\n");
    printf("Supported: +, -, *, /, ^, %%, sin, cos, tan, log, ln, sqrt, exp, abs, pow\n");
    printf("Constants: pi, e\n");
    printf("Enter expressions (Ctrl+D to exit):\n");
    yyparse();
    return 0;
}
