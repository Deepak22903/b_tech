#include <stdio.h>
#include <string.h>

// Function to convert a string to lowercase without using the string library function
void toLowerCase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32; // Convert uppercase to lowercase
        }
    }
}

// Function to convert a string to uppercase without using the string library function
void toUpperCase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32; // Convert lowercase to uppercase
        }
    }
}

int main() {
    char str[100];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    // Convert to lowercase using string library function
    char lowerStr[100];
    strcpy(lowerStr, str); // Copy the original string
    strlwr(lowerStr);     // Convert to lowercase

    // Convert to uppercase using string library function
    char upperStr[100];
    strcpy(upperStr, str); // Copy the original string
    strupr(upperStr);     // Convert to uppercase

    // Convert to lowercase without using string library function
    char lowerStrWithoutLib[100];
    strcpy(lowerStrWithoutLib, str); // Copy the original string
    toLowerCase(lowerStrWithoutLib);

    // Convert to uppercase without using string library function
    char upperStrWithoutLib[100];
    strcpy(upperStrWithoutLib, str); // Copy the original string
    toUpperCase(upperStrWithoutLib);

    printf("Original string: %s", str);
    printf("Lowercase (using library function): %s", lowerStr);
    printf("Uppercase (using library function): %s", upperStr);
    printf("Lowercase (without library function): %s", lowerStrWithoutLib);
    printf("Uppercase (without library function): %s", upperStrWithoutLib);

    return 0;
}
