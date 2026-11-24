class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        const long long LIMIT = 2520LL * 10;  // max possible lcm * gcd
        int best = 1;                          // a single element always qualifies

        for (int i = 0; i < n; i++) {
            long long p = 1, g = 0, l = 1;
            for (int j = i; j < n; j++) {
                long long x = nums[j];
                p *= x;
                if (p > LIMIT) break;          // prod >= lcm*gcd, can never match again
                g = __gcd(g, x);
                l = l / __gcd(l, x) * x;
                if (p == l * g) {
                    best = max(best, j - i + 1);
                }
            }
        }
        return best;
    }
};