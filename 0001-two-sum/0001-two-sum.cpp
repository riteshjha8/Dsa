class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int  n=nums.size();
        map<int,int> mp;

        for(int i=0; i<n; i++){
            int a=nums[i];
            int store=target-a;
            if(mp.find(store)!=mp.end()){
                return {mp[store],i};
            }
     mp[a]=i;
        }
        return {};
    }
};