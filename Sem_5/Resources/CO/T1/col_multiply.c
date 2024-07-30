// Create 2 matrices of size 1024x1024 and multiply them using tiled algorithm

#include <stdio.h>
#include <stdlib.h>

#define N 1024

int main() {
    int i, j, k, sum;
    int *a, *b, *c;

    a = (int *) malloc(N * N * sizeof(int));
    b = (int *) malloc(N * N * sizeof(int));
    c = (int *) malloc(N * N * sizeof(int));

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            a[i * N + j] = rand() % 10;
            b[i * N + j] = rand() % 10;
            c[i * N + j] = 0;
        }
    }

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            sum = 0;
            for (k = 0; k < N; k++) {
                sum += a[i * N + k] * b[k * N + j];
            }
            c[i * N + j] = sum;
        }
    }

    printf("Result matrix:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", c[i * N + j]);
        }
        printf("\n");
    }

    free(a);
    free(b);
    free(c);

    return 0;
}

