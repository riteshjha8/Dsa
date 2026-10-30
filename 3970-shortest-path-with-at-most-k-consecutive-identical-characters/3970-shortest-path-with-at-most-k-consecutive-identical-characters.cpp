class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        
        vector<vector<pair<int,int>>> adj(n);

        for (auto &e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
        }

        const long long INF = 1e18;

        vector<vector<long long>> dist(n, vector<long long>(k + 1, INF));

        using T = tuple<long long, int, int>;
        priority_queue<T, vector<T>, greater<T>> pq;

        dist[0][1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [d, u, run] = pq.top();
            pq.pop();

            if (d > dist[u][run]) continue;

            for (auto &[v, w] : adj[u]) {

                int newRun;

                if (labels[v] == labels[u]) {
                    newRun = run + 1;
                    if (newRun > k) continue;
                } else {
                    newRun = 1;
                }

                long long newDist = d + w;

                if (newDist < dist[v][newRun]) {
                    dist[v][newRun] = newDist;
                    pq.push({newDist, v, newRun});
                }
            }
        }

        long long ans = INF;

        for (int run = 1; run <= k; run++) {
            ans = min(ans, dist[n - 1][run]);
        }

        return ans == INF ? -1 : (int)ans;
    }
};