#include <stdio.h>
#include <ctype.h>

int vowel_1(){

    char c;
    printf("Enter a Character : ");
    scanf("%c", &c);

    c = tolower(c);

    if(c== 'a' || c== 'e' || c== 'i' || c== 'o' || c== 'u' ){
        printf("\nThe entered character is a 'Vowel'\n");
    } else{
        printf("\nThe entered character is a 'Consonent'\n");
    }
    
    return 0;
}