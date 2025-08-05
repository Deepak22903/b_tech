#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000

// Check if token is a keyword
int isKeyword(const char *token) {
  const char *keywords[] = {
      "auto",     "break",  "case",    "char",   "const",    "continue",
      "default",  "do",     "double",  "else",   "enum",     "extern",
      "float",    "for",    "goto",    "if",     "int",      "long",
      "register", "return", "short",   "signed", "sizeof",   "static",
      "struct",   "switch", "typedef", "union",  "unsigned", "void",
      "volatile", "while"};

  int n = sizeof(keywords) / sizeof(keywords[0]);
  for (int i = 0; i < n; ++i) {
    if (strcmp(token, keywords[i]) == 0)
      return 1;
  }
  return 0;
}

// Check if token is an operator
int isOperator(char ch) { return strchr("+-*/%=<>&|!", ch) != NULL; }

// Tokenize a line and classify tokens
void tokenize_line(char *line) {
  char *token = strtok(line, " \t\n\r;(){}[]<>=+-*/%!&|^,:\"");

  while (token != NULL) {
    if (isKeyword(token))
      printf("Keyword: %s\n", token);
    else if (isdigit(token[0]))
      printf("Constant: %s\n", token);
    else if (isalpha(token[0]) || token[0] == '_')
      printf("Identifier: %s\n", token);
    else
      printf("Other: %s\n", token);

    token = strtok(NULL, " \t\n\r;(){}[]<>=+-*/%!&|^,:\"");
  }
}

int main() {
  FILE *fptr = fopen("test.c", "r"); // <-- your C file

  if (fptr == NULL) {
    perror("Error opening file");
    return 1;
  }

  char line[MAX_LEN];
  printf("Tokenized output:\n\n");

  while (fgets(line, sizeof(line), fptr)) {
    tokenize_line(line);
  }

  fclose(fptr);
  return 0;
}
