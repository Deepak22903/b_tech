#include <stdio.h>
#include <stdlib.h>

typedef struct array{
    int *A;
    int size;
    int length;
}array;

void init(array *arr, int len){
    arr->A= (int *) malloc(len * sizeof(int));
    arr->size = len;
    arr->length = 0;
}

void append(array *arr, int d){
    if(arr->length < arr->size){
        arr->A[arr->length++] = d;
    }else{
        printf("Array is full");
    }
    return;
}

void display(array a){
    printf("[");
    for(int i = 0; i < a.length; i++){
        printf("%d ",a.A[i]);
    }
    printf("]");
}

void main(){
    array a;
    init(&a,5);
    append(&a,1);
    append(&a,2);
    append(&a,3);
    display(a);

}