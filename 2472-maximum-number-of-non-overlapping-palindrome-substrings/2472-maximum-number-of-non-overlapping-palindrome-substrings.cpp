class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();

        // palindrome[i][j] = true if s[i...j] is a palindrome
        vector<vector<bool>> palindrome(n, vector<bool>(n, false));

        // Build palindrome table
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {

                if (s[i] == s[j] &&
                    (j - i <= 2 || palindrome[i + 1][j - 1])) {
                    palindrome[i][j] = true;
                }
            }
        }

        // dp[i] = maximum number of palindromes
        // using the first i characters
        vector<int> dp(n + 1, 0);

        for (int r = 0; r < n; r++) {

            // Don't select a palindrome ending at r
            dp[r + 1] = dp[r];

            // Try every palindrome ending at r
            for (int l = 0; l <= r; l++) {

                if (r - l + 1 >= k && palindrome[l][r]) {
                    dp[r + 1] = max(dp[r + 1], dp[l] + 1);
                }
            }
        }

        return dp[n];
    }
};