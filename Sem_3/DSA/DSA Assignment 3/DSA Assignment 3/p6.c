#include <stdio.h>

int main() {
    int rows, cols;

    printf("Enter the number of rows and columns of the matrix: ");
    scanf("%d %d", &rows, &cols);

    if (rows <= 0 || cols <= 0) {
        printf("Invalid matrix dimensions.\n");
        return 1; 
    }

    int matrix[rows][cols];

    printf("Enter the elements of the matrix (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("Diagonal elements of the matrix:\n");
    int sum = 0;
    for (int i = 0; i < rows && i < cols; i++) {
        printf("%d ", matrix[i][i]); // Print the diagonal element
        sum += matrix[i][i];         // Add it to the sum
    }
    printf("\n");

    printf("Sum of diagonal elements: %d\n", sum);

    return 0;
}
