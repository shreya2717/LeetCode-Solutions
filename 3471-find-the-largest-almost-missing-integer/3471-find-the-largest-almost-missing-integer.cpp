class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();

        // count[x] = number of size-k subarrays containing x
        vector<int> count(51, 0);

        // Check every subarray of size k
        for (int i = 0; i <= n - k; i++) {
            vector<bool> seen(51, false);

            for (int j = i; j < i + k; j++) {
                int x = nums[j];

                // Count x only once in this subarray
                if (!seen[x]) {
                    count[x]++;
                    seen[x] = true;
                }
            }
        }

        // Find the largest integer appearing in exactly one subarray
        for (int x = 50; x >= 0; x--) {
            if (count[x] == 1) {
                return x;
            }
        }

        return -1;
    }
};