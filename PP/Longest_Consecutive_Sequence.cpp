#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        vector<int> track;
        sort(nums.begin(),nums.end());
        nums.erase(unique(nums.begin(),nums.end()),nums.end());
        int count=0;
        for(int i = 0; i < nums.size(); i++){
            if(nums[i]+1 == nums[i+1]){
                count++;
            }else{
                track.push_back(count+1);
                count=0;
            }
        }
        sort(track.begin(),track.end());
        return track.back();

    }
};


int main() {
    Solution sol;
    vector<int> nums = {2,20,4,10,3,4,5};
    cout << "Longest consecutive sequence length: " << sol.longestConsecutive(nums) << endl;
    return 0;
}