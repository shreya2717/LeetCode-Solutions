class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1000000007;

        int n = s.size();

        // dp[i] = number of distinct subsequences
        // (including empty) using first i characters
        vector<long long> dp(n + 1, 0);

        dp[0] = 1;

        // last[c] = dp value before the previous occurrence of c
        vector<long long> last(26, 0);

        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';

            dp[i + 1] = (2 * dp[i] - last[c] + MOD) % MOD;

            // For the next occurrence of this character,
            // the duplicate subsequences are based on dp[i].
            last[c] = dp[i];
        }

        // Remove the empty subsequence
        return (dp[n] - 1 + MOD) % MOD;
    }
};