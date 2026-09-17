class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();

        const int INF = 1e9;

        // best[i] = shortest valid subarray
        // completely inside arr[0 ... i-1]
        vector<int> best(n + 1, INF);

        int ans = INF;

        int left = 0;
        long long sum = 0;

        for (int right = 0; right < n; right++) {

            sum += arr[right];

            // Since all numbers are positive,
            // shrink the window if sum becomes too large.
            while (sum > target) {
                sum -= arr[left];
                left++;
            }

            // We found a subarray [left ... right]
            if (sum == target) {
                int len = right - left + 1;

                // Need another subarray completely before left
                if (best[left] != INF) {
                    ans = min(ans, len + best[left]);
                }

                // Store the shortest target subarray ending
                // at or before current position.
                best[right + 1] = min(best[right], len);
            }
            else {
                best[right + 1] = best[right];
            }
        }

        return ans == INF ? -1 : ans;
    }
};