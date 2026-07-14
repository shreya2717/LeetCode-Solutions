class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        const int MAX = 200;

        // dp[g1][g2] = number of ways to form two disjoint subsequences
        // having GCD g1 and g2
        // GCD 0 means the subsequence is empty
        vector<vector<long long>> dp(MAX + 1,
                                     vector<long long>(MAX + 1, 0));

        dp[0][0] = 1;

        for (int x : nums) {
            vector<vector<long long>> next = dp;

            for (int g1 = 0; g1 <= MAX; g1++) {
                for (int g2 = 0; g2 <= MAX; g2++) {
                    if (dp[g1][g2] == 0)
                        continue;

                    // Put x in seq1
                    int newG1 = gcd(g1, x);
                    next[newG1][g2] =
                        (next[newG1][g2] + dp[g1][g2]) % MOD;

                    // Put x in seq2
                    int newG2 = gcd(g2, x);
                    next[g1][newG2] =
                        (next[g1][newG2] + dp[g1][g2]) % MOD;
                }
            }

            dp = move(next);
        }

        long long ans = 0;

        // Both subsequences must be non-empty,
        // so their GCD must be greater than 0
        for (int g = 1; g <= MAX; g++) {
            ans = (ans + dp[g][g]) % MOD;
        }

        return ans;
    }
};