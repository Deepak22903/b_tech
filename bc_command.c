#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Node structure for linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to add two linked lists representing numbers
struct Node* addLinkedLists(struct Node* num1, struct Node* num2) {
    struct Node* result = NULL;
    struct Node* temp = NULL;
    struct Node* prev = NULL;
    int carry = 0, sum;

    while (num1 != NULL || num2 != NULL) {
        sum = carry + (num1 ? num1->data : 0) + (num2 ? num2->data : 0);

        carry = sum / 10;

        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->data = sum % 10;
        temp->next = NULL;

        if (result == NULL) {
            result = temp;
        } else {
            prev->next = temp;
        }

        if (num1) num1 = num1->next;
        if (num2) num2 = num2->next;

        prev = temp;
    }

    if (carry > 0) {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->data = carry;
        temp->next = NULL;
        prev->next = temp;
    }

    return result;
}

// Function to create a linked list from a string of digits
struct Node* createLinkedListFromNumber(char* number) {
    struct Node* head = NULL;
    struct Node* temp = NULL;
    struct Node* prev = NULL;

    int len = strlen(number);

    for (int i = len - 1; i >= 0; --i) {
        temp = (struct Node*)malloc(sizeof(struct Node));
        temp->data = number[i] - '0';
        temp->next = NULL;

        if (head == NULL) {
            head = temp;
        } else {
            prev->next = temp;
        }

        prev = temp;
    }

    return head;
}

// Function to free memory allocated for a linked list
void freeLinkedList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Function to evaluate a mathematical expression
struct Node* evaluateExpression(char* expression) {
    struct Node* result = NULL;
    struct Node* currentNumber = NULL;
    struct Node* tempNumber = NULL;
    char currentOperator = '+';

    int len = strlen(expression);

    for (int i = 0; i < len; ++i) {
        if (isdigit(expression[i])) {
            // Build the current number
            if (currentNumber == NULL) {
                currentNumber = createLinkedListFromNumber(&expression[i]);
            } else {
                tempNumber = createLinkedListFromNumber(&expression[i]);
                if (currentOperator == '+') {
                    currentNumber = addLinkedLists(currentNumber, tempNumber);
                } else {
                    // Handle other operations if needed
                }
                freeLinkedList(tempNumber);
            }

            // Move the index to the end of the current number
            while (i + 1 < len && isdigit(expression[i + 1])) {
                i++;
            }
        } else if (expression[i] == '+' || expression[i] == '-') {
            // Update the current operator
            currentOperator = expression[i];
        }
    }

    return currentNumber;
}

// Function to print a linked list
void printLinkedList(struct Node* head) {
    while (head != NULL) {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}



// Main function
int main() {
    char expression[100];

    printf("Enter a mathematical expression: ");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = '\0'; // Remove the newline character

    struct Node* result = evaluateExpression(expression);

    // Print the result
    printf("Result: ");
    printLinkedList(result);

    // Free allocated memory for linked lists
    freeLinkedList(result);

    return 0;
}
