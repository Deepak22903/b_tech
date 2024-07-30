#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the linked list
typedef struct Node {
    int row;
    int col;
    int value;
    struct Node* next;
} Node;

// Function to create a new node
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

int main() {
    FILE* file1 = fopen("Matrix1.txt", "r");
    FILE* file2 = fopen("Matrix2.txt", "r");

    if (file1 == NULL || file2 == NULL) {
        perror("Error opening the file(s)");
        return 1;
    }

    int numRows, numCols;
    fscanf(file1, "%d %d", &numRows, &numCols);

    Node* head1 = NULL;
    Node* head2 = NULL;
    Node* tail1 = NULL;
    Node* tail2 = NULL;

    // Read the first matrix (Matrix1.txt)
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            int value;
            fscanf(file1, "%d", &value);
            if (value != 0) {
                Node* newNode = createNode(i, j, value);
                if (head1 == NULL) {
                    head1 = newNode;
                    tail1 = newNode;
                } else {
                    tail1->next = newNode;
                    tail1 = newNode;
                }
            }
        }
    }

    // Read the second matrix (Matrix2.txt)
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            int value;
            fscanf(file2, "%d", &value);
            if (value != 0) {
                Node* newNode = createNode(i, j, value);
                if (head2 == NULL) {
                    head2 = newNode;
                    tail2 = newNode;
                } else {
                    tail2->next = newNode;
                    tail2 = newNode;
                }
            }
        }
    }

    fclose(file1);
    fclose(file2);

    // Perform addition and subtraction
    Node* current1 = head1;
    Node* current2 = head2;

    while (current1 != NULL && current2 != NULL) {
        if (current1->row == current2->row && current1->col == current2->col) {
            int sum = current1->value + current2->value;
            int diff = current1->value - current2->value;

            printf("Row: %d, Col: %d, Sum: %d, Diff: %d\n", current1->row, current1->col, sum, diff);

            current1 = current1->next;
            current2 = current2->next;
        } else {
            // Handle the case where the elements do not align
            printf("Elements do not align at Row: %d, Col: %d\n", current1->row, current1->col);
            current1 = current1->next;
            current2 = current2->next;
        }
    }

    // Close the output file

    return 0;
}
