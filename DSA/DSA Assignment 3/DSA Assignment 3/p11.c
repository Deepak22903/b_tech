#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    int frequency[256] = {0}; 

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    
    for (int i = 0; i < strlen(str); i++) {
        char ch = str[i];
        if (ch >= 'a' && ch <= 'z') {
            frequency[ch]++;
        } else if (ch >= 'A' && ch <= 'Z') {
            frequency[ch - 'A' + 'a']++; // Converting uppercase letters to lowercase
        }
    }

    printf("Character frequencies:\n");
    for (int i = 'a'; i <= 'z'; i++) {
        if (frequency[i] > 0) {
            printf("Frequency of %c = %d\n", i, frequency[i]);
        }
    }

    return 0;
}
