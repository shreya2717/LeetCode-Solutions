
class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        const int INF = 1e9;

        // Step 1: Precompute conversion cost
        vector<vector<int>> cost(n, vector<int>(n, INF));

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                int len = j - i + 1;

                // Try every valid divisor
                for (int d = 1; d < len; d++) {

                    if (len % d != 0)
                        continue;

                    int changes = 0;

                    // Compare mirrored characters
                    for (int p = 0; p < len; p++) {

                        int mirror =
                            (len / d - 1 - p / d) * d + p % d;

                        if (p < mirror &&
                            s[i + p] != s[i + mirror]) {
                            changes++;
                        }
                    }

                    cost[i][j] = min(cost[i][j], changes);
                }
            }
        }

        // Step 2: DP for partitioning
        vector<vector<int>> dp(
            n + 1, vector<int>(k + 1, INF)
        );

        dp[0][0] = 0;

        for (int parts = 1; parts <= k; parts++) {

            for (int i = 2 * parts; i <= n; i++) {

                // h = starting position of last substring
                for (int h = 2 * (parts - 1); h <= i - 2; h++) {

                    dp[i][parts] = min(
                        dp[i][parts],
                        dp[h][parts - 1] + cost[h][i - 1]
                    );
                }
            }
        }

        return dp[n][k];
    }
};
