class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();

        int pos0 = 0;
        while (nums[pos0] != 0) pos0++;

        bool inc = true;
        for (int i = 0; i < n; i++) {
            if (nums[(i + 1) % n] != (nums[i] + 1) % n) {
                inc = false;
                break;
            }
        }

        bool dec = true;
        for (int i = 0; i < n; i++) {
            if (nums[(i + 1) % n] != (nums[i] - 1 + n) % n) {
                dec = false;
                break;
            }
        }

        int ans = INT_MAX;

        if (inc) {
            int k = (n - pos0) % n;

            // only rotations
            ans = min(ans, pos0);

            // reverse -> rotate -> reverse
            ans = min(ans, k + 2);
        }

        if (dec) {
            int k = (n - 1 - pos0 + n) % n;

            // reverse first, then rotate
            ans = min(ans, k + 1);

            // rotate first, then reverse
            ans = min(ans, (n - k) % n + 1);
        }

        return ans == INT_MAX ? -1 : ans;
    }
};