#include <stdio.h>
#include <stdlib.h>
#include "List.c"

int main() {
    int numRows1, numCols1;
    Node* matrix1 = readMatrix("Matrix1.txt", &numRows1, &numCols1);

    int numRows2, numCols2;
    Node* matrix2 = readMatrix("Matrix2.txt", &numRows2, &numCols2);

    if (numRows1 != numRows2 || numCols1 != numCols2) {
        printf("The dimensions of the two matrices do not match.\n");
        return 1;
    }

    Node* sumResult = addMatrices(matrix1, matrix2, numRows1, numCols1);
    Node* diffResult = subtractMatrices(matrix1, matrix2, numRows1, numCols1);

    writeMatrixToFile("MatrixSum.txt", sumResult, numRows1, numCols1);
    writeMatrixToFile("MatrixDiff.txt", diffResult, numRows1, numCols1);

    return 0;
}
