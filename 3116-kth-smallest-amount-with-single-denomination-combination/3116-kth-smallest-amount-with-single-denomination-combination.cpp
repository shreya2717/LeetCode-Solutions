class Solution {
public:
    using ll = long long;

    ll gcdll(ll a, ll b) {
        while (b != 0) {
            ll temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }

    ll lcm(ll a, ll b) {
        return (a / gcdll(a, b)) * b;
    }

    bool check(ll x, vector<int>& coins, ll k) {
        int n = coins.size();
        ll count = 0;

        for (int mask = 1; mask < (1 << n); mask++) {

            ll common = 1;
            int bits = 0;
            bool tooLarge = false;

            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    bits++;

                    common = lcm(common, (ll)coins[i]);

                    if (common > x) {
                        tooLarge = true;
                        break;
                    }
                }
            }

            if (tooLarge)
                continue;

            ll cur = x / common;

            if (bits % 2 == 1)
                count += cur;
            else
                count -= cur;
        }

        return count >= k;
    }

    long long findKthSmallest(vector<int>& coins, int k) {

        ll left = 1;
        ll right = 100000000000LL; // 1e11

        while (left < right) {

            ll mid = left + (right - left) / 2;

            if (check(mid, coins, k))
                right = mid;
            else
                left = mid + 1;
        }

        return left;
    }
};
