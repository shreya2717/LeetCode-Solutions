class Solution {
public:
    int ans = INT_MAX;

    void dfs(int u, vector<vector<pair<int,int>>> &adj, vector<bool> &vis) {
        vis[u] = true;

        for (auto &[v, w] : adj[u]) {
            ans = min(ans, w);
            if (!vis[v]) {
                dfs(v, adj, vis);
            }
        }
    }

    int minScore(int n, vector<vector<int>>& roads) {
        vector<vector<pair<int,int>>> adj(n + 1);

        for (auto &e : roads) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        vector<bool> vis(n + 1, false);
        dfs(1, adj, vis);

        return ans;
    }
};