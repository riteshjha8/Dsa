class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int first = -1;
        int last = -1;

        auto lb = lower_bound(nums.begin(), nums.end(), target);

        if (lb == nums.end() || *lb != target)
            return {first, last};

        first = lb - nums.begin();

        auto ub = upper_bound(nums.begin(), nums.end(), target);
        last = (ub - nums.begin()) - 1;

        return {first, last};
    }
};