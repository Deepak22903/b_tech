#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n,sum;
    
    scanf("%d",&n);
    int *arr = (int *) malloc(n * sizeof(int)); 
    for(int i = 0; i < n; i++){
        scanf("%d",arr[i]);
    }
    
    for(int i = 0; i < n; i++){
        sum += arr[i];
    }
    
    printf("%d",sum);
    free(arr);
    return 0;
}