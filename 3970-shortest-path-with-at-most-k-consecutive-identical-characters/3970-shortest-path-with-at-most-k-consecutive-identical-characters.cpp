class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int,int>>> adj(n);
        for (auto& e : edges) adj[e[0]].push_back({e[1], e[2]});

        const long long INF = LLONG_MAX;
        int W = k + 1;
        vector<long long> dist((size_t)n * W, INF);
        dist[0 * W + 1] = 0;

        using T = tuple<long long, int, int>; // (distance, node, run)
        priority_queue<T, vector<T>, greater<T>> pq;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [d, u, run] = pq.top();
            pq.pop();
            if (d > dist[(size_t)u * W + run]) continue;
            if (u == n - 1) return (int)d;
            for (auto& [v, w] : adj[u]) {
                int nr = (labels[v] == labels[u]) ? run + 1 : 1;
                if (nr > k) continue;
                long long nd = d + w;
                size_t idx = (size_t)v * W + nr;
                if (nd < dist[idx]) {
                    dist[idx] = nd;
                    pq.push({nd, v, nr});
                }
            }
        }
        return -1;
    }
};