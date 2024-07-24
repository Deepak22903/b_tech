#include <stdio.h>

void bubble_sort(int arr[],int size){
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            if(arr[j] > arr[j + 1]){
                int temp = arr[j];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void insertion_sort(int arr[], int size){
    int i, key, j;
    for (i = 1; i < size; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int Linear_Search(int arr[],int size , int val){
    for(int i = 0; i < size; i++){
        if(arr[i] == val){
            return 1;
        }
    }
    return -1;
}

int Binary_Search(int arr[], int size, int val){
    int left = 0;
    int right = size -1;

    while(left <= right){
        int mid = left + (right -left)/2;

        if(arr[mid] == val){
            return 1;
        }else if(arr[mid] < val){
            left = mid +1;

        }else{
            right = mid -1;
        }
    }
    return -1;
}

void Bubble_sort(int arr[], int size){
    for(int i = 0; i < size -1; i++){
        for(int j = 0; j < size - i - 1; j++){
            if(arr[j] > arr[j + 1]){
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int binary_search(int arr[], int size, int find){
    int left = 0;
    int right = size -1;
    int mid;

    while(left  <= right){
        mid = left + (right - left)/2;

    if(arr[mid] == find){
        return 1;
    }else if(arr[mid] < find){
        left = mid +1;
    }else{
        right = mid -1;
    }
    }

    return -1;

}

void Selection_sort(int arr[], int size){
    int i,j,minIndex;

    for(i = 0 ; i< size; i++ ){
        minIndex = i;

        for(j = i + 1; j < size; j++){
            if(arr[j]< arr[minIndex]){
                minIndex = j;
            }
        }

        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }
}

int main(){
    int arr[]={1,5,6,7,8,2,3,4};
    int length = sizeof(arr)/sizeof(arr[0]);
    int find =5;
    int result = binary_search(arr,length,find);
    if(result == 1){
        printf("Found");
    }else if(result == -1){
        printf("Not Found");
    }
    insertion_sort(arr,length);
    for(int i = 0; i< length; i++){
        printf("%d ",arr[i]);
    }
    
    return 0;
}