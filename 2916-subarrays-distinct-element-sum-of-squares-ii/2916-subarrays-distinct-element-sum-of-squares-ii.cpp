class Solution {
public:
    int sumCounts(vector<int>& nums) {
        const long long MOD = 1000000007;
        int n = nums.size();

        vector<long long> treeSum(4 * n, 0);
        vector<long long> treeSq(4 * n, 0);
        vector<long long> lazy(4 * n, 0);

        auto apply = [&](int node, int l, int r, long long val) {
            long long len = r - l + 1;
            long long oldSum = treeSum[node];

            treeSq[node] = (
                treeSq[node]
                + 2LL * val % MOD * oldSum % MOD
                + val * val % MOD * len % MOD
            ) % MOD;

            treeSum[node] = (oldSum + val * len) % MOD;
            lazy[node] = (lazy[node] + val) % MOD;
        };

        auto push = [&](int node, int l, int r) {
            if (lazy[node] == 0 || l == r)
                return;

            int mid = l + (r - l) / 2;

            apply(node * 2, l, mid, lazy[node]);
            apply(node * 2 + 1, mid + 1, r, lazy[node]);

            lazy[node] = 0;
        };

        auto update = [&](auto&& self, int node, int l, int r,
                          int ql, int qr) -> void {
            if (ql <= l && r <= qr) {
                apply(node, l, r, 1);
                return;
            }

            push(node, l, r);

            int mid = l + (r - l) / 2;

            if (ql <= mid)
                self(self, node * 2, l, mid, ql, qr);

            if (qr > mid)
                self(self, node * 2 + 1, mid + 1, r, ql, qr);

            treeSum[node] = (
                treeSum[node * 2] + treeSum[node * 2 + 1]
            ) % MOD;

            treeSq[node] = (
                treeSq[node * 2] + treeSq[node * 2 + 1]
            ) % MOD;
        };

        unordered_map<int, int> lastSeen;
        long long ans = 0;

        for (int r = 0; r < n; r++) {
            int prev = -1;

            if (lastSeen.count(nums[r]))
                prev = lastSeen[nums[r]];

            update(update, 1, 0, n - 1, prev + 1, r);

            ans = (ans + treeSq[1]) % MOD;

            lastSeen[nums[r]] = r;
        }

        return static_cast<int>(ans);
    }
};