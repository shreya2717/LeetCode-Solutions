
class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {

        int n = nums.size();

        // Step 1: Calculate prefix sum
        vector<int> prefix(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        // Step 2: Initialize answer
        int ans = INT_MAX;

        // Step 3: Try every valid subarray length
        for (int len = l; len <= r; len++) {

            // Step 4: Enumerate all subarrays of this length
            for (int i = 0; i + len <= n; i++) {

                int sum = prefix[i + len] - prefix[i];

                // Step 5: Find minimum positive sum
                if (sum > 0) {
                    ans = min(ans, sum);
                }
            }
        }

        // Step 6: Return result
        return ans == INT_MAX ? -1 : ans;
    }
};
