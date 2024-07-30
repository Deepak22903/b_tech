class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> res;
        for(int i = 0; i < nums.size(); i++){
            int product=1;
            for(int j = 0; j < nums.size(); j++){
                if(j == i) continue;
                product = product * nums[j];
            }
            res.push_back(product);
        }
        return res;
    }
};
