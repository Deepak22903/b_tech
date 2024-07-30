#include <stdio.h>

int sum_for(int limit){
    int sum=0;
    for(int i=1; i<=limit; i++){
        sum = sum + i;
    }

    return sum;
}

int sum_while(int limit){
    int i=1;
    int sum=0;
    while(i <= limit){
        sum += i;
        i++;
    }

    return sum;

}

int main(){
    int limit;

    printf("Enter Limit: ");
    scanf("%d",&limit);

    printf("\n\nSum (for loop)= %d\n\n",sum_for(limit));
    printf("\n\nSum (while loop)= %d\n\n",sum_while(limit));

}
