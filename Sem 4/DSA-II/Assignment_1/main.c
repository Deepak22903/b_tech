#include <stdio.h>
#include "tree.h"

int main() {
    struct node* root = initBST();
    int choice, MIS;
    char name[50];

    do {
        printf("\nMenu:\n");
        printf("1. Insert Node\n");
        printf("2. Count Nodes\n");
        printf("3. Remove Node\n");
        printf("4. Search\n");
        printf("5. Inorder Traversal\n");
        printf("6. Preorder Traversal\n");
        printf("7. Postorder Traversal\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter MIS: ");
                scanf("%d", &MIS);
                printf("Enter Name: ");
                scanf("%s", name);
                root = insertNode(root, MIS, name);
                break;

            case 2:
                printf("Total Nodes: %d\n", countNodes(root));
                break;

            case 3:
                printf("Enter MIS to remove: ");
                scanf("%d", &MIS);
                root = removeNode(root, MIS);
                break;

            case 4:
                printf("Enter MIS to search: ");
                scanf("%d", &MIS);
                if (search(root, MIS) != NULL) {
                    printf("Node found!\n");
                } else {
                    printf("Node not found!\n");
                }
                break;

            case 5:
                printf("Inorder Traversal:\n");
                inorder(root);
                break;

            case 6:
                printf("Preorder Traversal:\n");
                preorder(root);
                break;

            case 7:
                printf("Postorder Traversal:\n");
                postorder(root);
                break;

            case 8:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 8);

    return 0;
}
