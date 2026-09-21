class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
       
        vector<long long> result(k, 0);
        vector<long long> dp(k, 0);

        for (int num : nums) {
            num %= k;
            vector<long long> newdp(k, 0);

            // extend previous subarrays
            for (int r = 0; r < k; r++) {
                if (dp[r]) {
                    int newr = (r * num) % k;
                    newdp[newr] += dp[r];
                }
            }

            // start new subarray
            newdp[num]++;

            // accumulate
            for (int r = 0; r < k; r++) {
                result[r] += newdp[r];
            }

            dp.swap(newdp); 
        }

        return result;
    }
};