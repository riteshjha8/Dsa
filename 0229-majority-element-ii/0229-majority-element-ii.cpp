class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int n=nums.size();
        unordered_map<int, int> mpp;
        int mm= (n/3)+1;
        vector<int> ans;
        for(int i=0; i<n; i++){
            mpp[nums[i]]++;
            if(mpp[nums[i]] == mm){
                ans.push_back(nums[i]);
            }
            if(ans.size()==2) break;
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};