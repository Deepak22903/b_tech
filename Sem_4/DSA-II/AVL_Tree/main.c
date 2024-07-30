#include "functions.c"

int main(){
    int choice;
    tree t1;
    init_AVL(&t1);
    char name[50];

    while(1){
        printf("\n1.Insert Node\n2.Delete Node\n3.Display\n4.Destroy Tree\n5.Exit");
        printf("\nEnter your Choice : ");
        scanf("%d",&choice);
        
        switch (choice)
        {
            case 1:
                printf("Enter Name of student to INSERT : ");
                scanf("%s", name);
                insertNode(&t1, name);
                break;

            case 2:
                printf("Enter Name of student to DELETE : ");
                scanf("%s", name);
                removeNode(&t1, name);
                break;

            case 3:
                printf("Student names in the tree: ");
                traverse(t1);
                printf("\n");
                break;

            case 4:
                destroyTree(&t1);
                printf("Tree destroyed.\n");
                break;
            
            case 5:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Enter a valid choice!\n");
                break;
        }
    }

    return 0;
}
