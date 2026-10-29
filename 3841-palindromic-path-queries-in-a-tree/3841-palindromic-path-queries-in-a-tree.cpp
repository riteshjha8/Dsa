class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int LOG = 1;
        while ((1 << LOG) <= n) ++LOG;

        vector<vector<int>> up(LOG, vector<int>(n));
        vector<int> tin(n), tout(n), depth(n);
        vector<int> pref(n);
        int timer = 0;

        // Iterative DFS avoids stack overflow on a long chain.
        vector<int> parent(n, 0), it(n, 0), st;
        st.reserve(n);
        st.push_back(0);
        parent[0] = 0;

        while (!st.empty()) {
            int u = st.back();

            if (it[u] == 0) {
                tin[u] = timer++;
                up[0][u] = parent[u];

                for (int j = 1; j < LOG; ++j)
                    up[j][u] = up[j - 1][up[j - 1][u]];

                pref[u] = (u == 0 ? 0 : pref[parent[u]])
                          ^ (1 << (s[u] - 'a'));
            }

            if (it[u] < (int)adj[u].size()) {
                int v = adj[u][it[u]++];
                if (v == parent[u]) continue;

                parent[v] = u;
                depth[v] = depth[u] + 1;
                st.push_back(v);
            } else {
                tout[u] = timer - 1;
                st.pop_back();
            }
        }

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);

            int d = depth[u] - depth[v];
            for (int j = 0; j < LOG; ++j)
                if (d & (1 << j))
                    u = up[j][u];

            if (u == v) return u;

            for (int j = LOG - 1; j >= 0; --j) {
                if (up[j][u] != up[j][v]) {
                    u = up[j][u];
                    v = up[j][v];
                }
            }
            return up[0][u];
        };

        // Range-XOR updates and point queries.
        vector<int> bit(n + 2, 0);

        auto add = [&](int idx, int val) {
            for (++idx; idx <= n; idx += idx & -idx)
                bit[idx] ^= val;
        };

        auto rangeXor = [&](int l, int r, int val) {
            add(l, val);
            if (r + 1 < n) add(r + 1, val);
        };

        auto pointQuery = [&](int idx) {
            int res = 0;
            for (++idx; idx > 0; idx -= idx & -idx)
                res ^= bit[idx];
            return res;
        };

        // Initial root-prefix masks are computed by DFS.
        // A node update toggles its bit throughout its subtree.
        vector<bool> ans;

        for (const string &query : queries) {
            stringstream ss(query);
            string type;
            int u;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int delta = (1 << (s[u] - 'a')) ^ (1 << (c - 'a'));
                if (delta) {
                    rangeXor(tin[u], tout[u], delta);
                    s[u] = c;
                }
            } else {
                int v;
                ss >> v;

                int w = lca(u, v);
                int pu = pref[u] ^ pointQuery(tin[u]);
                int pv = pref[v] ^ pointQuery(tin[v]);

                int mask = pu ^ pv ^ (1 << (s[w] - 'a'));
                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};