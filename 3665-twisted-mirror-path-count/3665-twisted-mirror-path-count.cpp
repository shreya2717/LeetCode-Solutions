class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        const int MOD = 1e9 + 7;

        vector<vector<long long>> dp(m, vector<long long>(n, 0));
        dp[0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[i][j] == 0) continue;

                for (int dir = 0; dir < 2; dir++) {
                    int r = i;
                    int c = j;
                    int d = dir;

                    if (d == 0) c++;
                    else r++;

                    while (r < m && c < n && grid[r][c] == 1) {
                        if (d == 0) r++;
                        else c++;

                        d ^= 1;
                    }

                    if (r < m && c < n) {
                        dp[r][c] = (dp[r][c] + dp[i][j]) % MOD;
                    }
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};