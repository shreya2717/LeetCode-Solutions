class Solution {
public:
    int n;
    vector<int> suffix;
    vector<vector<int>> dp;

    int solve(int i, int M) {
        // All piles are already taken
        if (i >= n)
            return 0;

        // If we can take all remaining piles
        if (2 * M >= n - i)
            return suffix[i];

        if (dp[i][M] != -1)
            return dp[i][M];

        int ans = 0;

        // Try taking X piles, where 1 <= X <= 2*M
        for (int X = 1; X <= 2 * M && i + X <= n; X++) {

            // Alice takes X piles.
            // Bob then gets the best possible result from the rest.
            int bob = solve(i + X, max(M, X));

            // Total remaining stones - Bob's maximum
            int alice = suffix[i] - bob;

            ans = max(ans, alice);
        }

        return dp[i][M] = ans;
    }

    int stoneGameII(vector<int>& piles) {
        n = piles.size();

        // suffix[i] = total stones from i to n-1
        suffix.resize(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        dp.assign(n, vector<int>(n + 1, -1));

        return solve(0, 1);
    }
};