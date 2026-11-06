class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
     sort(logs.begin(), logs.end(),
     [](const vector<int>& a, const vector<int>& b) {
         return a[1] < b[1];
     });
        int q = queries.size();
        vector<pair<int, int>> qs;

        for (int i = 0; i < q; i++) {
            qs.push_back({queries[i], i});
        }

        sort(qs.begin(), qs.end());

        vector<int> ans(q);
        vector<int> freq(n + 1, 0);

        int activeServers = 0;
        int left = 0, right = 0;
        int m = logs.size();

        for (auto& [time, idx] : qs) {
            int start = time - x;

            while (right < m && logs[right][1] <= time) {
                int server = logs[right][0];
                if (++freq[server] == 1) {
                    activeServers++;
                }
                right++;
            }

            while (left < right && logs[left][1] < start) {
                int server = logs[left][0];
                if (--freq[server] == 0) {
                    activeServers--;
                }
                left++;
            }

            ans[idx] = n - activeServers;
        }

        return ans;
    }
};