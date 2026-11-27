class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        int mn = INT_MAX;
        for (auto& it : items) mn = min(mn, it[1]);

        // cnt[i] = copies gained from the first purchase of item i
        vector<int> cnt(n, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (items[j][0] % items[i][0] == 0) cnt[i]++;
            }
        }

        // 0/1 knapsack over first purchases
        vector<int> f(budget + 1, 0);
        for (int i = 0; i < n; i++) {
            int price = items[i][1];
            for (int b = budget; b >= price; b--) {
                f[b] = max(f[b], f[b - price] + cnt[i]);
            }
        }

        // leftover budget buys plain copies of the cheapest item
        int ans = 0;
        for (int b = 0; b <= budget; b++) {
            ans = max(ans, f[b] + (budget - b) / mn);
        }
        return ans;
    }
};