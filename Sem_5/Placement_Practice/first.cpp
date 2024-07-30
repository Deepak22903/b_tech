#include <iostream>
#include <array>

using namespace std;

int main(){
    // int arr[5] = {1,2,3,4,5};
    // cout<<arr[3];
    array<int,5> arr1 =  {1,2,3,4,5};
    for(int i:arr1){
        cout<<i<<endl;
    }
}