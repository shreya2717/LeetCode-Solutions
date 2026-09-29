class Solution {
public:
    int m, n;
    vector<vector<vector<int>>> dp;

    bool dfs(vector<vector<char>>& grid, int i, int j, int balance) {

        // Add current bracket
        if (grid[i][j] == '(')
            balance++;
        else
            balance--;

        // Invalid prefix
        if (balance < 0)
            return false;

        // Too many '(' to close with remaining cells
        int remaining = (m - 1 - i) + (n - 1 - j);

        if (balance > remaining)
            return false;

        // Reached destination
        if (i == m - 1 && j == n - 1)
            return balance == 0;

        // Already calculated
        if (dp[i][j][balance] != -1)
            return dp[i][j][balance];

        bool ans = false;

        // Move down
        if (i + 1 < m) {
            ans = ans || dfs(grid, i + 1, j, balance);
        }

        // Move right
        if (j + 1 < n) {
            ans = ans || dfs(grid, i, j + 1, balance);
        }

        return dp[i][j][balance] = ans;
    }

    bool hasValidPath(vector<vector<char>>& grid) {

        m = grid.size();
        n = grid[0].size();

        // Path length must be even
        if ((m + n - 1) % 2 == 1)
            return false;

        // First must be '('
        if (grid[0][0] == ')')
            return false;

        // Last must be ')'
        if (grid[m - 1][n - 1] == '(')
            return false;

        dp.assign(
            m,
            vector<vector<int>>(
                n,
                vector<int>(m + n, -1)
            )
        );

        return dfs(grid, 0, 0, 0);
    }
};