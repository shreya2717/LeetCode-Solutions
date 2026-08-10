class Solution {
public:
    bool winnerSquareGame(int n) {
        vector<bool> dp(n + 1, false);

        // dp[i] = true if the current player can win
        // when there are i stones.

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j * j <= i; j++) {

                // If removing j*j stones leaves a losing
                // position for the opponent, we can win.
                if (!dp[i - j * j]) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};