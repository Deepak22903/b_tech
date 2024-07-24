#include <stdio.h>

void inputMatrix(int rows, int cols, int matrix[rows][cols])
{
    printf("Enter elements of the matrix (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void printMatrix(int rows, int cols, int matrix[rows][cols])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void addMatrices(int rows, int cols, int matrix1[rows][cols], int matrix2[rows][cols], int result[rows][cols])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}
void subtractMatrices(int rows, int cols, int matrix1[rows][cols], int matrix2[rows][cols], int result[rows][cols])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
}

void multiplyMatrices(int rows1, int cols1, int matrix1[rows1][cols1], int rows2, int cols2, int matrix2[rows2][cols2], int result[rows1][cols2])
{
    if (cols1 != rows2)
    {
        printf("Matrix multiplication is not possible. Number of columns in the first matrix must be equal to the number of rows in the second matrix.\n");
        return;
    }

    for (int i = 0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            result[i][j] = 0;
            for (int k = 0; k < cols1; k++)
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

int main()
{
    int rows1, cols1, rows2, cols2;

    printf("Enter the number of rows and columns for the first matrix: ");
    scanf("%d %d", &rows1, &cols1);

    printf("Enter the number of rows and columns for the second matrix: ");
    scanf("%d %d", &rows2, &cols2);

    if (rows1 <= 0 || cols1 <= 0 || rows2 <= 0 || cols2 <= 0 || cols1 != rows2)
    {
        printf("Invalid matrix dimensions.\n");
        return 1; 
    }

    int matrix1[rows1][cols1], matrix2[rows2][cols2], result[rows1][cols2];

    printf("Matrix operations menu:\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("Enter your choice (1/2/3): ");
    int choice;
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        inputMatrix(rows1, cols1, matrix1);
        inputMatrix(rows2, cols2, matrix2);
        addMatrices(rows1, cols1, matrix1, matrix2, result);
        printf("Result of addition:\n");
        printMatrix(rows1, cols1, result);
        break;
    case 2:
        inputMatrix(rows1, cols1, matrix1);
        inputMatrix(rows2, cols2, matrix2);
        subtractMatrices(rows1, cols1, matrix1, matrix2, result);
        printf("Result of subtraction:\n");
        printMatrix(rows1, cols1, result);
        break;
    case 3:
        inputMatrix(rows1, cols1, matrix1);
        inputMatrix(rows2, cols2, matrix2);
        multiplyMatrices(rows1, cols1, matrix1, rows2, cols2, matrix2, result);
        printf("Result of multiplication:\n");
        printMatrix(rows1, cols2, result);
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }

    return 0;
}
