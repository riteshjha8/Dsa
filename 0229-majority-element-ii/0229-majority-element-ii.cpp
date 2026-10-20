class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int n=nums.size();
        map<int, int> mpp;
        int mm= (n/3)+1;
        vector<int> ans;
        for(int i=0; i<n; i++){
            mpp[nums[i]]++;
            if(mpp[nums[i]] == mm){
                ans.push_back(nums[i]);
            }
        }
        return ans;
    }
};