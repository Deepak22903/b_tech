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

void insert(array *arr, int pos, int d){
    if(arr->length < arr->size && pos >= arr->length){
        return;
    }else{
        int i = arr->length;
        while(i >= pos){
            arr->A[i+1] = arr->A[i];
            i--;
        }
        arr->A[pos] = d;
        arr->length++;
    }
    return;
}

void delete(array *arr, int pos){
    if(arr->length < 0){
        return;
    }else{
        int i = pos;
        while(i < arr->length){
            arr->A[i] = arr->A[i+1];
            i++;
        }
        arr->length--;
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

int min_ele(array arr){
    int min = arr.A[0];
    for(int i = 0; i < arr.length; i++){
        if(arr.A[i] < min){
            min = arr.A[i];
        }
    }
    return min;
}

int max_ele(array arr){
    int max = arr.A[0];
    for(int i = 0; i < arr.length; i++){
        if(arr.A[i] > max){
            max = arr.A[i];
        }
    }
    return max;
}

array merge(array a, array b){
    array c;
    init(&c,a.length + b.length);

    for(int i = 0; i < a.length; i++){
        append(&c,a.A[i]);
    }

    for(int i = 0; i < b.length; i++){
        append(&c,b.A[i]);
    }

    return c;
}

void reverse(array *arr){
    int start = 0;
    int end = arr->length -1;
    int temp;

    while(start < end){
        temp = arr->A[start];
        arr->A[start]=arr->A[end];
        arr->A[end] = temp;
        start++;
        end--;
    }
    return;
}

void main(){
    array b;
    init(&b,5);
    append(&b,10);
    array a;
    init(&a,5);
    append(&a,1);
    append(&a,2);
    append(&a,3);
    insert(&a,1,4);
    insert(&a,3,5);
    delete(&a,1);
    delete(&a,2);
    display(a);
    printf("\nMinimum : %d \n Maximum : %d\n",min_ele(a),max_ele(a));
    printf("\n");
    display(merge(a,b));
    reverse(&a);
    display(a);
}