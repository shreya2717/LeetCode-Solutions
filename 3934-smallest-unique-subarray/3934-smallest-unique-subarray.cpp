class Solution {
    typedef unsigned long long ull;
    static constexpr ull MOD = (1ULL << 61) - 1;

    static ull mulmod(ull a, ull b) {
        __uint128_t t = (__uint128_t)a * b;
        ull r = (ull)(t & MOD) + (ull)(t >> 61);
        if (r >= MOD) r -= MOD;
        if (r >= MOD) r -= MOD;
        return r;
    }

public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        ull B = rng() % (MOD - 1000000) + 500000;

        vector<ull> h(n + 1, 0), pw(n + 1, 1);
        for (int i = 0; i < n; i++) {
            h[i + 1] = (mulmod(h[i], B) + (ull)nums[i]) % MOD;
            pw[i + 1] = mulmod(pw[i], B);
        }

        // Does some window of length L occur exactly once?
        auto hasUnique = [&](int L) -> bool {
            int m = n - L + 1;
            vector<ull> v(m);
            for (int i = 0; i < m; i++) {
                ull x = h[i + L] + MOD - mulmod(h[i], pw[L]);
                if (x >= MOD) x -= MOD;
                v[i] = x;
            }
            sort(v.begin(), v.end());
            for (int i = 0; i < m; i++) {
                bool diffPrev = (i == 0) || v[i] != v[i - 1];
                bool diffNext = (i == m - 1) || v[i] != v[i + 1];
                if (diffPrev && diffNext) return true;
            }
            return false;
        };

        int lo = 1, hi = n;          // L = n is always unique
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (hasUnique(mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};