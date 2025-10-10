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

%type <dval> expression

/* Precedence and associativity for ambiguous grammar */
%left PLUS MINUS
%left TIMES DIVIDE MOD
%right POWER
%nonassoc UMINUS

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

/* AMBIGUOUS GRAMMAR - using operator precedence */
expression:
    NUMBER                              { $$ = $1; }
    | expression PLUS expression        { $$ = $1 + $3; }
    | expression MINUS expression       { $$ = $1 - $3; }
    | expression TIMES expression       { $$ = $1 * $3; }
    | expression DIVIDE expression      { 
        if ($3 == 0) {
            yyerror("Division by zero");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
    }
    | expression POWER expression       { $$ = pow($1, $3); }
    | expression MOD expression         { $$ = fmod($1, $3); }
    | MINUS expression %prec UMINUS     { $$ = -$2; }
    | LPAREN expression RPAREN          { $$ = $2; }
    | SIN LPAREN expression RPAREN      { $$ = sin($3); }
    | COS LPAREN expression RPAREN      { $$ = cos($3); }
    | TAN LPAREN expression RPAREN      { $$ = tan($3); }
    | LOG LPAREN expression RPAREN      { $$ = log10($3); }
    | LN LPAREN expression RPAREN       { $$ = log($3); }
    | SQRT LPAREN expression RPAREN     { $$ = sqrt($3); }
    | EXP LPAREN expression RPAREN      { $$ = exp($3); }
    | ABS LPAREN expression RPAREN      { $$ = fabs($3); }
    | POW LPAREN expression COMMA expression RPAREN { $$ = pow($3, $5); }
    ;

%%

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Scientific Calculator (Ambiguous Grammar)\n");
    printf("Supported: +, -, *, /, ^, %%, sin, cos, tan, log, ln, sqrt, exp, abs, pow\n");
    printf("Constants: pi, e\n");
    printf("Enter expressions (Ctrl+D to exit):\n");
    yyparse();
    return 0;
}
