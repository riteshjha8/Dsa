class Solution {
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {

        struct Node {
            int p = 1;
            int cnt[5] = {};
        };

        auto merge = [&](Node a, Node b) {
            Node c;

            c.p = (a.p * b.p) % k;

            for (int i = 0; i < k; i++) {
                c.cnt[i] += a.cnt[i];
            }

            for (int i = 0; i < k; i++) {
                int rem = (a.p * i) % k;
                c.cnt[rem] += b.cnt[i];
            }

            return c;
        };

        int n = nums.size();

        vector<Node> tree(2 * n);

        // Build leaves
        for (int i = 0; i < n; i++) {
            int rem = nums[i] % k;

            tree[n + i].p = rem;
            tree[n + i].cnt[rem] = 1;
        }

        // Build tree
        for (int i = n - 1; i > 0; i--) {
            tree[i] = merge(tree[i * 2], tree[i * 2 + 1]);
        }

        vector<int> ans;

        for (auto &q : queries) {

            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Update
            int pos = n + index;

            tree[pos] = Node();

            int rem = value % k;

            tree[pos].p = rem;
            tree[pos].cnt[rem] = 1;

            pos /= 2;

            while (pos > 0) {
                tree[pos] = merge(tree[pos * 2],
                                   tree[pos * 2 + 1]);
                pos /= 2;
            }

            // Query [start, n-1]
            int l = n + start;
            int r = n + n;

            Node leftResult;
            Node rightResult;

            while (l < r) {

                if (l & 1) {
                    leftResult = merge(leftResult, tree[l]);
                    l++;
                }

                if (r & 1) {
                    --r;
                    rightResult = merge(tree[r], rightResult);
                }

                l /= 2;
                r /= 2;
            }

            Node result = merge(leftResult, rightResult);

            ans.push_back(result.cnt[x]);
        }

        return ans;
    }
};