
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> tree(n);

        // Build the original tree
        for (int i = 1; i < n; i++) {
            tree[parent[i]].push_back(i);
        }

        vector<int> ans(n, 1);
        vector<int> last(26, -1);

        function<void(int)> dfs = [&](int u) {

            int c = s[u] - 'a';

            // Store previous occurrence
            int prev = last[c];

            // Current node becomes the latest occurrence
            last[c] = u;

            // Visit children
            for (int v : tree[u]) {
                dfs(v);
            }

            // Find the new parent
            int newParent = (prev != -1) ? prev : parent[u];

            // Add subtree size to the new parent
            if (newParent != -1) {
                ans[newParent] += ans[u];
            }

            // Backtracking
            last[c] = prev;
        };

        dfs(0);

        return ans;
    }
};
