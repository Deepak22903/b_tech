#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include<string.h>

int main() {
    int line_number = 1;
    int token_num = 0;
    char token[100];
    char c;

    FILE *input_file = fopen("program.c", "r"); 
    FILE *output_file = fopen("output.txt", "w"); 
    
    if (!input_file || !output_file) {
        perror("Error opening files");
        return 1;
    }

    fprintf(output_file, "Line no. Token no. Token             Lexeme\n");

    while ((c = fgetc(input_file)) != EOF) {
        if (c == '\n') {
            line_number++;
        } else if (isspace(c)) {
            continue;
        } else if (c == '#') {
            while ((c = fgetc(input_file)) != '\n' && c != EOF) {
                // Do nothing, consume characters until end of line or file
            }
            line_number++;
        } else if (isalpha(c) || c == '_') {
            // Identifiers and Keywords
            int i = 0;
            token[i++] = c;
            while (isalnum(c = fgetc(input_file)) || c == '_') {
                token[i++] = c;
            }
            token[i] = '\0';

            if (strcmp(token, "void") == 0 || strcmp(token, "main") == 0) {
                fprintf(output_file, "%d\t%d\tKeyword\t%s\n", line_number, ++token_num, token);
            } else {
                fprintf(output_file, "%d\t%d\tIdentifier\t%s\n", line_number, ++token_num, token);
            }
        } else if (c == '(' || c == ')' || c == '{' || c == '}' || c == ';') {
            // Special characters
            fprintf(output_file, "%d\t%d\t%c\t%c\n", line_number, ++token_num, c, c);
        } else if (c == '"') {
            // String literals
            int i = 0;
            token[i++] = c;
            while ((c = fgetc(input_file)) != '"' && c != EOF) {
                token[i++] = c;
            }
            token[i++] = '"';
            token[i] = '\0';

            fprintf(output_file, "%d\t%d\tLiteral\t%s\n", line_number, ++token_num, token);
        }
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}

