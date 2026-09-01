class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
     int n = nums.size();
     if(nums.empty()) return 0;
     int insert=1;
    for(int i=1; i<n;i++){
        if(nums[i]!=nums[i-1]){
            nums[insert]=nums[i];
           insert =insert+1;
        }
    }
    return insert;
    }
};