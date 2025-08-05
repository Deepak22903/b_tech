#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void write_to_file(const char *filename) {
  FILE *fptr = fopen(filename, "w");
  if (fptr == NULL) {
    printf("Error creating file.\n");
    exit(1);
  }
  fprintf(fptr, "Hello, File Handling in C!\n");
  fprintf(fptr, "This is a test file.\n");
  fclose(fptr);
  printf("Data written successfully.\n\n");
}

void read_file(const char *filename) {
  FILE *fptr = fopen(filename, "r");
  char ch;

  if (fptr == NULL) {
    printf("Error opening file.\n");
    exit(1);
  }

  printf("Reading file contents:\n");
  while ((ch = fgetc(fptr)) != EOF) {
    putchar(ch);
  }
  fclose(fptr);
  printf("\n");
}

void append_to_file(const char *filename) {
  FILE *fptr = fopen(filename, "a");
  if (fptr == NULL) {
    printf("Error opening file for appending.\n");
    exit(1);
  }
  fprintf(fptr, "This line was appended.\n");
  fclose(fptr);
  printf("Data appended successfully.\n\n");
}

void count_stats(const char *filename) {
  FILE *fptr = fopen(filename, "r");
  char ch;
  int chars = 0, words = 0, lines = 0;
  int in_word = 0;

  if (fptr == NULL) {
    printf("Error reading file.\n");
    exit(1);
  }

  while ((ch = fgetc(fptr)) != EOF) {
    chars++;

    if (ch == '\n')
      lines++;

    if (isspace(ch))
      in_word = 0;
    else if (!in_word) {
      in_word = 1;
      words++;
    }
  }

  fclose(fptr);

  printf("File Statistics:\n");
  printf("Characters: %d\n", chars);
  printf("Words: %d\n", words);
  printf("Lines: %d\n\n", lines);
}

int main() {
  const char *filename = "sample.txt";

  write_to_file(filename);
  read_file(filename);
  append_to_file(filename);
  read_file(filename);
  count_stats(filename);

  return 0;
}
