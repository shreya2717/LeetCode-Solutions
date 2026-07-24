class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;

        vector<vector<bool>> dp(4, vector<bool>(MAXX, false));
        dp[0][0] = true;

        vector<bool> ans(MAXX, false);

        for (int v : nums) {
            ans[v] = true;  // triplets with repeated indices

            for (int cnt = 2; cnt >= 0; cnt--) {
                for (int x = 0; x < MAXX; x++) {
                    if (dp[cnt][x])
                        dp[cnt + 1][x ^ v] = true;
                }
            }
        }

        for (int x = 0; x < MAXX; x++)
            if (dp[3][x]) ans[x] = true;

        int res = 0;
        for (bool b : ans) res += b;
        return res;
    }
};