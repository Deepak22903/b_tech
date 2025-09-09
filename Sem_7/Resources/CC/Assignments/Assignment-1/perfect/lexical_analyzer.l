%{
#include <stdio.h>
#include <ctype.h>
%}

%%
"auto"          { printf("KEYWORD: auto\n"); }
"break"         { printf("KEYWORD: break\n"); }
"case"          { printf("KEYWORD: case\n"); }
"char"          { printf("KEYWORD: char\n"); }
"const"         { printf("KEYWORD: const\n"); }
"continue"      { printf("KEYWORD: continue\n"); }
"default"       { printf("KEYWORD: default\n"); }
"do"            { printf("KEYWORD: do\n"); }
"double"        { printf("KEYWORD: double\n"); }
"else"          { printf("KEYWORD: else\n"); }
"enum"          { printf("KEYWORD: enum\n"); }
"extern"        { printf("KEYWORD: extern\n"); }
"float"         { printf("KEYWORD: float\n"); }
"for"           { printf("KEYWORD: for\n"); }
"goto"          { printf("KEYWORD: goto\n"); }
"if"            { printf("KEYWORD: if\n"); }
"int"           { printf("KEYWORD: int\n"); }
"long"          { printf("KEYWORD: long\n"); }
"register"      { printf("KEYWORD: register\n"); }
"return"        { printf("KEYWORD: return\n"); }
"short"         { printf("KEYWORD: short\n"); }
"signed"        { printf("KEYWORD: signed\n"); }
"sizeof"        { printf("KEYWORD: sizeof\n"); }
"static"        { printf("KEYWORD: static\n"); }
"struct"        { printf("KEYWORD: struct\n"); }
"switch"        { printf("KEYWORD: switch\n"); }
"typedef"       { printf("KEYWORD: typedef\n"); }
"union"         { printf("KEYWORD: union\n"); }
"unsigned"      { printf("KEYWORD: unsigned\n"); }
"void"          { printf("KEYWORD: void\n"); }
"volatile"      { printf("KEYWORD: volatile\n"); }
"while"         { printf("KEYWORD: while\n"); }
"inline"        { printf("KEYWORD: inline\n"); }
"restrict"      { printf("KEYWORD: restrict\n"); }
"_Bool"         { printf("KEYWORD: _Bool\n"); }
"_Complex"      { printf("KEYWORD: _Complex\n"); }
"_Imaginary"    { printf("KEYWORD: _Imaginary\n"); }

[a-zA-Z_][a-zA-Z0-9_]* { printf("IDENTIFIER: %s\n", yytext); }

"=="            { printf("OPERATOR: ==\n"); }
"!="            { printf("OPERATOR: !=\n"); }
"<="            { printf("OPERATOR: <=\n"); }
">="            { printf("OPERATOR: >=\n"); }
"&&"            { printf("OPERATOR: &&\n"); }
"||"            { printf("OPERATOR: ||\n"); }
"++"            { printf("OPERATOR: ++\n"); }
"--"            { printf("OPERATOR: --\n"); }
"+"             { printf("OPERATOR: +\n"); }
"-"             { printf("OPERATOR: -\n"); }
"*"             { printf("OPERATOR: *\n"); }
"/"             { printf("OPERATOR: /\n"); }
"<"             { printf("OPERATOR: <\n"); }
">"             { printf("OPERATOR: >\n"); }
"="             { printf("OPERATOR: =\n"); }
"&"             { printf("OPERATOR: &\n"); }
"|"             { printf("OPERATOR: |\n"); }
"^"             { printf("OPERATOR: ^\n"); }
"~"             { printf("OPERATOR: ~\n"); }
"!"             { printf("OPERATOR: !\n"); }
"<<"            { printf("OPERATOR: <<\n"); }
">>"            { printf("OPERATOR: >>\n"); }
"+="            { printf("OPERATOR: +=\n"); }
"-="            { printf("OPERATOR: -=\n"); }
"*="            { printf("OPERATOR: *=\n"); }
"/="            { printf("OPERATOR: /=\n"); }
"%="            { printf("OPERATOR: %%=\n"); }
"&="            { printf("OPERATOR: &=\n"); }
"|="            { printf("OPERATOR: |=\n"); }
"^="            { printf("OPERATOR: ^=\n"); }
"<<="           { printf("OPERATOR: <<=\n"); }
">>="           { printf("OPERATOR: >>=\n"); }

[0-9]+          { printf("NUMBER: %s\n", yytext); }
[0-9]+"."[0-9]+ { printf("NUMBER: %s\n", yytext); }

"("             { printf("SYMBOL: (\n"); }
")"             { printf("SYMBOL: )\n"); }
"{"             { printf("SYMBOL: {\n"); }
"}"             { printf("SYMBOL: }\n"); }
"["             { printf("SYMBOL: [\n"); }
"]"             { printf("SYMBOL: ]\n"); }
";"             { printf("SYMBOL: ;\n"); }
","             { printf("SYMBOL: ,\n"); }
"."             { printf("SYMBOL: .\n"); }
"->"            { printf("SYMBOL: ->\n"); }

[ \t\n]         ;

.               { printf("UNKNOWN CHARACTER: %s\n", yytext); }

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening file");
            return 1;
        }
        yyin = file; // Use yyin to point to the input file
    }
    yylex();
    return 0;
}

