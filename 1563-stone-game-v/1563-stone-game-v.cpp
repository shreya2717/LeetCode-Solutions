#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + stoneValue[i];

        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                int best = 0;
                for (int k = i; k < j; k++) {
                    long long leftSum = prefix[k + 1] - prefix[i];
                    long long rightSum = prefix[j + 1] - prefix[k + 1];
                    int leftDp = dp[i][k];
                    int rightDp = dp[k + 1][j];
                    int cur;
                    if (leftSum < rightSum) {
                        // left row is smaller -> left survives
                        cur = (int)leftSum + leftDp;
                    } else if (leftSum > rightSum) {
                        // right row is smaller -> right survives
                        cur = (int)rightSum + rightDp;
                    } else {
                        // tie -> Alice picks whichever half gives a better future
                        cur = (int)leftSum + max(leftDp, rightDp);
                    }
                    best = max(best, cur);
                }
                dp[i][j] = best;
            }
        }

        return dp[0][n - 1];
    }
};