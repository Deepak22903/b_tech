#include <stdio.h>

int main() {
    int n;

    printf("Enter the size of the square matrix: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid matrix size.\n");
        return 1;
    }

    int matrix[n][n];

    printf("Enter the elements of the square matrix (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("Upper Triangular Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j < i) {
                printf("\t"); // Print a tab for lower triangular elements
            } else {
                printf("%d\t", matrix[i][j]); // Print upper triangular elements
            }
        }
        printf("\n");
    }

    printf("Lower Triangular Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j > i) {
                printf("\t"); // Print a tab for upper triangular elements
            } else {
                printf("%d\t", matrix[i][j]); // Print lower triangular elements
            }
        }
        printf("\n");
    }

    return 0;
}
