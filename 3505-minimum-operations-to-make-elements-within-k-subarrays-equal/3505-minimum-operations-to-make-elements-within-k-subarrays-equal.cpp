class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        vector<long long> cost(n - x + 1);

        multiset<long long> left, right;
        long long leftSum = 0, rightSum = 0;

        auto balance = [&]() {
            while (left.size() > right.size() + 1) {
                auto it = prev(left.end());
                long long v = *it;
                left.erase(it);
                leftSum -= v;

                right.insert(v);
                rightSum += v;
            }

            while (left.size() < right.size()) {
                auto it = right.begin();
                long long v = *it;
                right.erase(it);
                rightSum -= v;

                left.insert(v);
                leftSum += v;
            }
        };

        auto add = [&](long long v) {
            if (left.empty() || v <= *prev(left.end())) {
                left.insert(v);
                leftSum += v;
            } else {
                right.insert(v);
                rightSum += v;
            }
            balance();
        };

        auto remove = [&](long long v) {
            auto it = left.find(v);

            if (it != left.end()) {
                left.erase(it);
                leftSum -= v;
            } else {
                it = right.find(v);
                right.erase(it);
                rightSum -= v;
            }
            balance();
        };

        for (int i = 0; i < x; i++) add(nums[i]);

        auto getCost = [&]() {
            long long med = *prev(left.end());

            long long c1 = med * (long long)left.size() - leftSum;
            long long c2 = rightSum - med * (long long)right.size();

            return c1 + c2;
        };

        cost[0] = getCost();

        for (int i = x; i < n; i++) {
            add(nums[i]);
            remove(nums[i - x]);
            cost[i - x + 1] = getCost();
        }

        int m = cost.size();

        vector<vector<long long>> dp(m + 1,
            vector<long long>(k + 1, 1e18));

        for (int i = 0; i <= m; i++) dp[i][0] = 0;

        for (int i = m - 1; i >= 0; i--) {
            for (int j = 1; j <= k; j++) {

                dp[i][j] = dp[i + 1][j];

                int nxt = i + x;

                long long take = cost[i];

                if (nxt <= m)
                    take += dp[nxt][j - 1];
                else if (j > 1)
                    take = 1e18;

                dp[i][j] = min(dp[i][j], take);
            }
        }

        return dp[0][k];
    }
};