#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main(){
    while(1){
        char str[50];
        printf("prompt> ");
        scanf("%s",str);
        if(strcmp(str,"ls") == 0){
            execlp("ls","ls",NULL);
        }
    }
}