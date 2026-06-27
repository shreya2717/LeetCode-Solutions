class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> freq;

        for (int x : nums)
            freq[x]++;

        int ans = 1;

        // Special case for 1
        if (freq.count(1)) {
            int cnt = freq[1];
            ans = max(ans, (cnt % 2) ? cnt : cnt - 1);
        }

        for (auto &p : freq) {
            long long cur = p.first;

            if (cur == 1) continue;

            int extend = 0;

            while (freq[cur] >= 2) {
                long long nxt = cur * cur;

                if (!freq.count(nxt))
                    break;

                extend++;
                cur = nxt;
            }

            ans = max(ans, 2 * extend + 1);
        }

        return ans;
    }
};
