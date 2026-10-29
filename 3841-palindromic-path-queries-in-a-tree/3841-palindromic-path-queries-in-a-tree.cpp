class Solution {
    int n, LOG = 16;
    vector<int> bit;
    void upd(int i, int v) { for (i++; i <= n + 1; i += i & -i) bit[i] ^= v; }
    int qry(int i) { int r = 0; for (i++; i > 0; i -= i & -i) r ^= bit[i]; return r; }

public:
    vector<bool> palindromePath(int n_, vector<vector<int>>& edges, string s, vector<string>& queries) {
        n = n_;
        bit.assign(n + 2, 0);
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        vector<int> tin(n), tout(n), depth(n, 0), init(n, 0);
        vector<vector<int>> up(LOG + 1, vector<int>(n, 0));

        // iterative DFS from root 0
        int timer = 0;
        vector<int> idx(n, 0), stk;
        stk.push_back(0);
        up[0][0] = 0;
        tin[0] = timer++;
        init[0] = 1 << (s[0] - 'a');
        while (!stk.empty()) {
            int u = stk.back();
            if (idx[u] < (int)g[u].size()) {
                int v = g[u][idx[u]++];
                if (v == up[0][u] && u != 0) continue;
                if (u == 0 && v == 0) continue;
                up[0][v] = u;
                depth[v] = depth[u] + 1;
                init[v] = init[u] ^ (1 << (s[v] - 'a'));
                tin[v] = timer++;
                stk.push_back(v);
            } else {
                tout[u] = timer - 1;
                stk.pop_back();
            }
        }
        for (int k = 1; k <= LOG; k++)
            for (int v = 0; v < n; v++)
                up[k][v] = up[k - 1][up[k - 1][v]];

        auto lca = [&](int a, int b) {
            if (depth[a] < depth[b]) swap(a, b);
            int diff = depth[a] - depth[b];
            for (int k = 0; k <= LOG; k++)
                if (diff >> k & 1) a = up[k][a];
            if (a == b) return a;
            for (int k = LOG; k >= 0; k--)
                if (up[k][a] != up[k][b]) {
                    a = up[k][a];
                    b = up[k][b];
                }
            return up[0][a];
        };
        auto getP = [&](int x) { return init[x] ^ qry(tin[x]); };

        vector<bool> ans;
        for (auto& q : queries) {
            istringstream ss(q);
            string type;
            ss >> type;
            if (type == "update") {
                int u; char c;
                ss >> u >> c;
                int d = (1 << (s[u] - 'a')) ^ (1 << (c - 'a'));
                if (d) {
                    upd(tin[u], d);
                    upd(tout[u] + 1, d);
                    s[u] = c;
                }
            } else {
                int u, v;
                ss >> u >> v;
                int l = lca(u, v);
                int mask = getP(u) ^ getP(v) ^ (1 << (s[l] - 'a'));
                ans.push_back((mask & (mask - 1)) == 0);
            }
        }
        return ans;
    }
};