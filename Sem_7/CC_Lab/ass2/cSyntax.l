
%{
#include <stdio.h>
#include <string.h>

char *keywords[] = {
    "int", "float", "if", "else", "while", "for", "return", "char", "double", "void", "switch", "case", "default", "break"
};

int is_keyword(char *str) {
    for (int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}
%}

/* Macros */
DIGIT      [0-9]
ID         [a-zA-Z_][a-zA-Z0-9_]*
WS         [ \t\n]+
STRING     \"([^\\\"]|\\.)*\"
CHAR       \'([^\\\']|\\.)\'
COMMENT1   "//".*
COMMENT2   "/*"([^*]|\*+[^*/])*\*+"/"

%%
"#".*                { printf("Preprocessor: %s\n", yytext); }

{COMMENT1}           { printf("Comment: %s\n", yytext); }
{COMMENT2}           { printf("Comment: %s\n", yytext); }

{STRING}             { printf("String: %s\n", yytext); }
{CHAR}               { printf("Char: %s\n", yytext); }

{ID}                 {
                        if (is_keyword(yytext))
                            printf("Keyword: %s\n", yytext);
                        else
                            printf("Identifier: %s\n", yytext);
                     }

{DIGIT}+             { printf("Number: %s\n", yytext); }

"+"|"-"|"*"|"/"|"%"  { printf("Operator: %s\n", yytext); }

"="|"<"|">"|"=="|"!="|"<="|">="   { printf("Operator: %s\n", yytext); }

";"|"{"|"}"|"("|")"|","   { printf("Symbol: %s\n", yytext); }

{WS}                 { /* ignore whitespace */ }

.                    { printf("Unknown: %s\n", yytext); }
%%

int main() {
    yylex();
    return 0;
}

