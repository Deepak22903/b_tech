#include <stdio.h>
#include <stdlib.h>

typedef struct arr {
    int *A;
    int size;
    int length;
} array;

void init(array *arr, int size){
    arr->A = (int *) malloc(size * sizeof(int));
    arr->size = size;
    arr->length = 0;
    return;
}

void append(array *arr, int element){
    if(arr->length < arr->size){
        arr->A[arr->length++]= element;
    }
    return;
}

void insert(array *arr, int pos, int ele){
    int i;
    if(pos < 0 || pos >= arr->length){
        return;
    }

    i = arr->length -1;

    while(i >= pos){
        arr->A[i + 1] = arr->A[i];
        i--;
    }
    
    arr->A[pos] = ele;
    arr->length++;
    return;
}

void remove_element(array *arr, int pos){
    int i;
    if(pos < 0 || pos >= arr->length){
        return;
    }

    i = pos;

    while(i < (arr->length - 1)){
        arr->A[i] = arr->A[i+1];
        i++;
    }

    arr->length--;
    return;
}

void reverse(array *arr){
    int start = 0;
    int end = arr->length -1;
    int temp;

    while(start < end){
        temp = arr->A[start];
        arr->A[start] = arr->A[end];
        arr->A[end] = temp;

        start++;
        end--;
    }
    return;
}

int max_ele(array arr){
    int maximum = arr.A[0];
    for(int i = 0; i < (arr.length); i++){
        if(arr.A[i] > maximum){
            maximum = arr.A[i];
        }
    }
    return maximum;
}

int min_ele(array arr){
    int mini = arr.A[0];

    for (int i = 0; i < arr.length; i++){
        if(arr.A[i] < mini){
            mini = arr.A[i];
        }
    }
    return mini;
}

array merge_array(array a, array b){
    array merged;
    init(&merged,a.length+ b.length);

    for (int i = 0; i<a.length; i++){
        append(&merged,a.A[i]);
    }

    for(int i = 0; i < b.length; i++){
        append(&merged,b.A[i]);
    }

    return merged;

}

void print(array arr){
    for(int i = 0; i<arr.length; i++){
        printf(" %d |",arr.A[i]);
    }
    return;
}

int main(){
    array a,b;
    init(&b,5);
    init(&a,5);
    append(&a,1);
    append(&a,2);
    append(&a,4);
    append(&b,5);
    append(&b,6);
    append(&b,7);
    insert(&a,2,3);
    remove_element(&a,1);
    reverse(&a);
    int min = min_ele(a);
    int max = max_ele(a);
    
    printf("First Array : \n");
    print(a);
    printf("\nSecond Array : \n");
    print(b);
    printf("\n Maximum = %d",max);
    printf("\n Minimum = %d", min);
    printf("\n Merged Array : \n");
    print(merge_array(a,b));
}