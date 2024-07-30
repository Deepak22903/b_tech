#include "list.h"

// Initialize the linked list
void init(list* head) {
    *head = NULL;  // Set the head pointer to NULL, indicating an empty list
    return;
}

// Append a new node to the linked list with given row, column, and value
void append(list* head, int r, int c, int val) {
    node* new, *p;
    new = (node*)malloc(sizeof(node));  // Allocate memory for a new node
    if (new) {
        // Initialize the new node with provided values
        new->r = r;
        new->c = c;
        new->val = val;
        new->next = NULL;  // Set the next pointer to NULL as it will be the last node
    }
    else return;  // Return if memory allocation fails

    if (*head == NULL) {
        *head = new;  // If the list is empty, make the new node the head of the list
        return;
    }

    p = *head;
    while (p->next) {
        p = p->next;  // Traverse to the end of the list
    }
    p->next = new;  // Append the new node to the end of the list
    return;
}

// Perform matrix addition and store the result in a new linked list
void sum(list* head1, list* head2, list* res) {
    node* p, *q;
    p = *head1;
    q = *head2;

    while (p && q) {
        if (p->r == q->r) {
            if (p->c == q->c) {
                // If rows and columns match, add the values and append to the result list
                append(res, p->r, p->c, p->val + q->val);
                p = p->next;
                q = q->next;
            }
            else if (p->c < q->c) {
                // If columns are not equal, append the smaller column value to the result list
                append(res, p->r, p->c, p->val);
                p = p->next;
            }
            else {
                // If columns are not equal, append the smaller column value to the result list
                append(res, p->r, q->c, q->val);
                q = q->next;
            }
        }
        else if (p->r < q->r) {
            // If rows are not equal, append the smaller row value to the result list
            append(res, p->r, p->c, p->val);
            p = p->next;
        }
        else {
            // If rows are not equal, append the smaller row value to the result list
            append(res, q->r, q->c, q->val);
            q = q->next;
        }
    }

    // Add remaining nodes from both lists
    while (p) {
        append(res, p->r, p->c, p->val);
        p = p->next;
    }

    while (q) {
        append(res, q->r, q->c, q->val);
        q = q->next;
    }
    return;
}

// Perform matrix subtraction and store the result in a new linked list
void sub(list* head1, list* head2, list* res) {
    node* p, *q;
    p = *head1;
    q = *head2;

    while (p && q) {
        if (p->r == q->r) {
            if (p->c == q->c) {
                // If rows and columns match, subtract the values and append to the result list
                append(res, p->r, p->c, p->val - q->val);
                p = p->next;
                q = q->next;
            }
            else if (p->c < q->c) {
                // If columns are not equal, append the smaller column value to the result list
                append(res, p->r, p->c, p->val);
                p = p->next;
            }
            else {
                // If columns are not equal, append the smaller column value to the result list
                append(res, p->r, q->c, -1 * q->val);
                q = q->next;
            }
        }
        else if (p->r < q->r) {
            // If rows are not equal, append the smaller row value to the result list
            append(res, p->r, p->c, p->val);
            p = p->next;
        }
        else {
            // If rows are not equal, append the smaller row value to the result list
            append(res, q->r, q->c, -1 * q->val);
            q = q->next;
        }
    }

    // Add remaining nodes from both lists
    while (p) {
        append(res, p->r, p->c, p->val);
        p = p->next;
    }

    while (q) {
        append(res, q->r, q->c, -1 * q->val);
        q = q->next;
    }
    return;
}

// Display the elements of the linked list
void display(list l) {
    while (l) {
        printf("[%d %d %d] ", l->r, l->c, l->val);
        l = l->next;
    }
    return;
}
