#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to allocate memory for a matrix with given dimensions
int** allocateMatrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}

// Function to deallocate memory for a matrix
void deallocateMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int rows1 = 1024, cols1 = 1024;
    int rows2 = 1024, cols2 = 1024;

    // Check if matrix multiplication is possible
    if (cols1 != rows2) {
        printf("Matrix multiplication is not possible. The number of columns in the first matrix must be equal to the number of rows in the second matrix.\n");
        return 1; // Return an error code
    }

    // Allocate memory for matrices
    int** matrix1 = allocateMatrix(rows1, cols1);
    int** matrix2 = allocateMatrix(rows2, cols2);
    int** result = allocateMatrix(rows1, cols2);

    // Fill matrices with random values
    srand(time(NULL)); // Seed the random number generator with current time

    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols1; j++) {
            matrix1[i][j] = rand() % 100; // Generates random numbers between 0 and 99
        }
    }

    for (int i = 0; i < rows2; i++) {
        for (int j = 0; j < cols2; j++) {
            matrix2[i][j] = rand() % 100; // Generates random numbers between 0 and 99
        }
    }

    // Initialize the result matrix with zeros
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            result[i][j] = 0;
        }
    }

    // Perform matrix multiplication
    for (int j = 0; j < rows1; j++) {
        for (int i = 0; i < cols2; i++) {
            for (int k = 0; k < cols1; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    // Deallocate memory for matrices
    deallocateMatrix(matrix1, rows1);
    deallocateMatrix(matrix2, rows2);
    deallocateMatrix(result, rows1);

    return 0;
}
