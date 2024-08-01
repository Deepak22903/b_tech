#include <iostream>
#include <vector>

using namespace std;

vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> res;
        int start = 0;
        int end = numbers.size() -1;
        while(start < end){
            int current_sum = numbers[start] + numbers[end];
            if(current_sum == target){
                start ++;
                end++;
                res.push_back(start);
                res.push_back(end);
                return res;
            }
            if(current_sum < target){
                start++;
            }else{
                end--;
            }
        }
        return res;   
}

// Example usage:
int main() {
    vector<int> numbers = {1, 2, 3, 4};
    int target = 3;
    vector<int> result = twoSum(numbers, target);
    cout << "[" << result[0] << ", " << result[1] << "]" << endl; // Output: [1, 2]
    return 0;
}

