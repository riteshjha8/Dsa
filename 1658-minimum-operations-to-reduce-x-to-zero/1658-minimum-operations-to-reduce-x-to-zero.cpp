class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int total = 0;
        for (int num : nums) total += num;
        
        int target = total - x;
        if (target < 0) return -1;  // impossible case
        
        int n = nums.size();
        int left = 0, currSum = 0, maxLen = -1;
        
        for (int right = 0; right < n; right++) {
            currSum += nums[right];
            
            // shrink window if sum exceeds target
            while (left <= right && currSum > target) {
                currSum -= nums[left];
                left++;
            }
            
            if (currSum == target) {
                maxLen = max(maxLen, right - left + 1);
            }
        }
        
        return (maxLen == -1) ? -1 : n - maxLen;
    }
};
