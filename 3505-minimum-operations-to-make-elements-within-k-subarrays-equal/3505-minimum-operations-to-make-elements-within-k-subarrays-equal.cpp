class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        multiset<int> low, high;
        long long sumLow = 0, sumHigh = 0;

        auto rebalance = [&]() {
            int target = (x + 1) / 2;

            while ((int)low.size() > target) {
                auto it = prev(low.end());
                int val = *it;
                low.erase(it);
                sumLow -= val;
                high.insert(val);
                sumHigh += val;
            }

            while ((int)low.size() < target && !high.empty()) {
                auto it = high.begin();
                int val = *it;
                high.erase(it);
                sumHigh -= val;
                low.insert(val);
                sumLow += val;
            }
        };

        auto add = [&](int val) {
            if (low.empty() || val <= *low.rbegin()) {
                low.insert(val);
                sumLow += val;
            } else {
                high.insert(val);
                sumHigh += val;
            }
            rebalance();
        };

        auto remove = [&](int val) {
            auto it = low.find(val);

            if (it != low.end()) {
                low.erase(it);
                sumLow -= val;
            } else {
                it = high.find(val);
                high.erase(it);
                sumHigh -= val;
            }

            rebalance();
        };

        auto getCost = [&]() -> long long {
            long long median = *low.rbegin();

            return median * (long long)low.size() - sumLow
                 + sumHigh - median * (long long)high.size();
        };

        // Cost of making every window equal.
        vector<long long> cost(n - x + 1);

        for (int i = 0; i < x; i++) {
            add(nums[i]);
        }

        cost[0] = getCost();

        for (int i = x; i < n; i++) {
            remove(nums[i - x]);
            add(nums[i]);

            cost[i - x + 1] = getCost();
        }

        // dp[i][j] = minimum cost using the first i elements
        // to select exactly j non-overlapping subarrays.
        const long long INF = LLONG_MAX / 4;

        vector<vector<long long>> dp(
            n + 1, vector<long long>(k + 1, INF)
        );

        dp[0][0] = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= k; j++) {
                if (dp[i][j] == INF)
                    continue;

                // Skip the current element.
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);

                // Select a subarray of size x.
                if (j < k && i + x <= n) {
                    dp[i + x][j + 1] = min(
                        dp[i + x][j + 1],
                        dp[i][j] + cost[i]
                    );
                }
            }
        }

        return dp[n][k];
    }
};