class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);
        vector<long long> dp(k, 0);

        for (int num : nums) {
            vector<long long> ndp(k, 0);

            int x = num % k;

            // Start a new subarray with nums[i]
            ndp[x]++;

            // Extend previous subarrays
            for (int r = 0; r < k; r++) {
                int newRemainder = (r * x) % k;
                ndp[newRemainder] += dp[r];
            }

            // Add all subarrays ending at current position
            for (int r = 0; r < k; r++) {
                ans[r] += ndp[r];
            }

            dp = ndp;
        }

        return ans;
    }
};