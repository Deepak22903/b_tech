#include <stdio.h>
#include <ctype.h>

int vowel_2(){

    char c;

    printf("Enter a Character : ");
    scanf("%c", &c);

    c = tolower(c);

    if (c >= 'a' && c <= 'z'){

        switch (c)
        {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        printf("\nThe entered character is a 'Vowel'\n");
        break;
        
        default:
        printf("\nThe entered character is a 'Consonent'\n");
            break;
        }
    } else{
        printf("Please enter a valid character");
    }

    return 0;
}