#include<stdio.h>
#include<stdlib.h>

int main(){
    FILE *fp;
    int flag;

    fp = fopen("input.txt", "r");
    if(fp == NULL){
        printf("Error opening file\n");
        exit(1);
    }else{
        printf("File opened successfully\n");
    }

    // Counting number of lines
    int count = 0;
    char c;
    
    flag=0;
    for(c = getc(fp); c != EOF; c = getc(fp)){
        if(c == '\n'){
            count++;
        }
        flag=1;
    }
    if (flag){
        count++;
    }
    printf("Number of lines: %d\n", count);

    // Counting number of words and characters
    rewind(fp);
    int wordCount = 0;
    int charCount = 0;
    char ch;
    flag=1;
    for(ch = getc(fp); ch != EOF; ch = getc(fp)){
        if(ch == ' ' || ch == '\n'){
            flag = 1;
            charCount++;
            continue;
        }
        if (flag){
            wordCount++;
            flag = 0;
        }
        charCount++;

    }
    // if (flag){
    //     wordCount++;
    // }

    printf("Number of words: %d\n", wordCount);
    printf("Number of characters: %d\n", charCount);
    rewind(fp);

    // Add Line Number at the starting of each line
    FILE *fp2;
    fp2 = fopen("test2.txt", "w");
    char ch2;

    int lineCount = 1;
    fprintf(fp2, "%d ", lineCount);
    for(ch2 = getc(fp); ch2 != EOF; ch2 = getc(fp)){
        if(ch2 == '\n'){
            lineCount++;
            fprintf(fp2, "\n%d ", lineCount);
        }else{
            fprintf(fp2, "%c", ch2);
        }
    }

    fclose(fp);
    fclose(fp2);

    return 0;
}