#include <stdio.h>
#include <string.h>

// Function to find the length of a string without using the standard library function
int stringLength(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Function to copy a string without using the standard library function
void stringCopy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Function to compare two strings without using the standard library function
int stringCompare(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i]) {
        i++;
    }
    if (str1[i] < str2[i]) {
        return -1;
    } else if (str1[i] > str2[i]) {
        return 1;
    } else {
        return 0;
    }
}

// Function to concatenate two strings without using the standard library function
void stringConcatenate(char *dest, const char *src) {
    int destLength = stringLength(dest);
    int i = 0;
    while (src[i] != '\0') {
        dest[destLength + i] = src[i];
        i++;
    }
    dest[destLength + i] = '\0';
}

// Function to reverse a string without using the standard library function
void stringReverse(char *str) {
    int length = stringLength(str);
    int i, j;
    for (i = 0, j = length - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

// Function to find a substring within a string without using the standard library function
int findSubstring(const char *str, const char *sub) {
    int i, j, found;
    int strLen = stringLength(str);
    int subLen = stringLength(sub);

    for (i = 0; i <= strLen - subLen; i++) {
        found = 1;
        for (j = 0; j < subLen; j++) {
            if (str[i + j] != sub[j]) {
                found = 0;
                break;
            }
        }
        if (found) {
            return i; // Return the index where the substring is found
        }
    }

    return -1; // Return -1 if substring is not found
}

int main() {
    char str1[100], str2[100], result[200], substring[100];
    int choice, length, compareResult, foundIndex;

    printf("Enter the first string: ");
    scanf("%s", str1);

    while (1) {
        printf("\nString Operations Menu:\n");
        printf("1. Find length\n");
        printf("2. Copy\n");
        printf("3. Compare\n");
        printf("4. Concatenate\n");
        printf("5. Reverse\n");
        printf("6. Find Substring\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                length = stringLength(str1);
                printf("Length of the string: %d\n", length);
                break;
            case 2:
                stringCopy(str2, str1);
                printf("Copied string: %s\n", str2);
                break;
            case 3:
                printf("Enter the second string to compare: ");
                scanf("%s", str2);
                compareResult = stringCompare(str1, str2);
                if (compareResult == 0) {
                    printf("Strings are equal.\n");
                } else if (compareResult < 0) {
                    printf("String 1 is less than String 2.\n");
                } else {
                    printf("String 1 is greater than String 2.\n");
                }
                break;
            case 4:
                printf("Enter the second string to concatenate: ");
                scanf("%s", str2);
                stringCopy(result, str1);
                stringConcatenate(result, str2);
                printf("Concatenated string: %s\n", result);
                break;
            case 5:
                stringCopy(result, str1);
                stringReverse(result);
                printf("Reversed string: %s\n", result);
                break;
            case 6:
                printf("Enter the substring to find: ");
                scanf("%s", substring);
                foundIndex = findSubstring(str1, substring);
                if (foundIndex != -1) {
                    printf("Substring found at index %d\n", foundIndex);
                } else {
                    printf("Substring not found in the string.\n");
                }
                break;
            case 7:
                return 0; // Exit the program
            default:
                printf("Invalid choice.\n");
                break;
        }
    }

    return 0;
}
