class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
       
          long long result[5] = {0}; 
        long long dp[5] = {0}; 

        for (int num : nums) {
            num %= k;
            long long newdp[5] = {0};

            for (int r = 0; r < k; r++) {
                if (dp[r]) {
                    int newr = (r * num) % k;
                    newdp[newr] += dp[r];
                }
            }

            newdp[num]++;

            for (int r = 0; r < k; r++) {
                result[r] += newdp[r];
                dp[r] = newdp[r]; // overwrite directly instead of swap
            }
        }

        return vector<long long>(result, result + k);
    }
};