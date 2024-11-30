#include <stdio.h>

int main() {
  int array[10];
  FILE *trace = fopen("memory_trace.txt", "w");

  for (int i = 0; i < 10; i++) {
    fprintf(trace, "R %p 4\n", &array[i]); // Log read access with size
    array[i] = i;                          // Write access
    fprintf(trace, "W %p 4\n", &array[i]); // Log write access with size
  }

  fclose(trace);
  return 0;
}
