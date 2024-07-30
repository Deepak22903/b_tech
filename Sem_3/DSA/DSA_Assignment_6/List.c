#include <stdio.h>
#include <stdlib.h>
#include "List.h"

Node* createNode(int row, int col, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

Node* readMatrix(const char* filename, int* numRows, int* numCols) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening the file");
        exit(1);
    }

    fscanf(file, "%d %d", numRows, numCols);

    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 0; i < *numRows; i++) {
        for (int j = 0; j < *numCols; j++) {
            int value;
            fscanf(file, "%d", &value);
            if (value != 0) {
                // Create a new node for the non-zero element
                Node* newNode = createNode(i, j, value);
                if (head == NULL) {
                    head = newNode;
                    tail = newNode;
                } else {
                    tail->next = newNode;
                    tail = newNode;
                }
            }
        }
    }

    fclose(file);

    return head;
}

void printMatrix(Node* result, int numRows, int numCols) {
    int** matrix = (int**)malloc(sizeof(int*) * numRows);
    for (int i = 0; i < numRows; i++) {
        matrix[i] = (int*)malloc(sizeof(int) * numCols);
        for (int j = 0; j < numCols; j++) {
            matrix[i][j] = 0;
        }
    }

    Node* current = result;
    while (current != NULL) {
        matrix[current->row][current->col] = current->value;
        current = current->next;
    }

    // Print the matrix
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Free dynamically allocated memory for the matrix
    for (int i = 0; i < numRows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

Node* addMatrices(Node* matrix1, Node* matrix2, int numRows, int numCols) {
    Node* result = NULL;
    Node* current1 = matrix1;
    Node* current2 = matrix2;

    while (current1 != NULL || current2 != NULL) {
        if (current1 == NULL || (current2 != NULL && (current1->row > current2->row || (current1->row == current2->row && current1->col > current2->col)))) {
            // Add the element from matrix2
            Node* newNode = createNode(current2->row, current2->col, current2->value);
            newNode->value = current2->value;
            newNode->next = result;
            result = newNode;
            current2 = current2->next;
        } else if (current2 == NULL || (current1 != NULL && (current1->row < current2->row || (current1->row == current2->row && current1->col < current2->col)))) {
            // Add the element from matrix1
            Node* newNode = createNode(current1->row, current1->col, current1->value);
            newNode->value = current1->value;
            newNode->next = result;
            result = newNode;
            current1 = current1->next;
        } else {
            // Both matrices have an element at the same position
            // Add the values and create a new element
            int sum = current1->value + current2->value;
            int diff = current1->value - current2->value;
            if (sum != 0) {
                Node* newNode = createNode(current1->row, current1->col, sum);
                newNode->next = result;
                result = newNode;
            }
            if (diff != 0) {
                Node* newNode = createNode(current1->row, current1->col, diff);
                newNode->next = result;
                result = newNode;
            }
            current1 = current1->next;
            current2 = current2->next;
        }
    }
    return result;
}

Node* subtractMatrices(Node* matrix1, Node* matrix2, int numRows, int numCols) {
    Node* result = NULL;
    Node* current1 = matrix1;
    Node* current2 = matrix2;

    while (current1 != NULL || current2 != NULL) {
        if (current1 == NULL || (current2 != NULL && (current1->row > current2->row || (current1->row == current2->row && current1->col > current2->col)))) {
            // Subtract the element from matrix2
            Node* newNode = createNode(current2->row, current2->col, -current2->value);
            newNode->next = result;
            result = newNode;
            current2 = current2->next;
        } else if (current2 == NULL || (current1 != NULL && (current1->row < current2->row || (current1->row == current2->row && current1->col < current2->col)))) {
            // Subtract the element from matrix1
            Node* newNode = createNode(current1->row, current1->col, current1->value);
            newNode->next = result;
            result = newNode;
            current1 = current1->next;
        } else {
            // Both matrices have an element at the same position
            // Subtract the values and create a new element
            int diff = current1->value - current2->value;
            if (diff != 0) {
                Node* newNode = createNode(current1->row, current1->col, diff);
                newNode->next = result;
                result = newNode;
            }
            current1 = current1->next;
            current2 = current2->next;
        }
    }

    return result;
}

void writeMatrixToFile(const char* filename, Node* matrix, int numRows, int numCols) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening the file for writing");
        exit(1);
    }

    // Write the matrix dimensions to the file
    fprintf(file, "%d \n%d\n", numRows, numCols);

    // Write the matrix elements to the file
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            int value = 0;  // Default value is 0
            Node* current = matrix;
            while (current != NULL) {
                if (current->row == i && current->col == j) {
                    value = current->value;
                    break;
                }
                current = current->next;
            }
            fprintf(file, "%d ", value);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}
