class Solution {
public:
    static const int MOD = 1000000007;

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.size();

        vector<int> nzPos;
        vector<int> nzDigit;

        vector<long long> prefSum(n + 1, 0);

        for (int i = 0; i < n; i++) {
            int d = s[i] - '0';
            prefSum[i + 1] = prefSum[i] + d;
            if (d != 0) {
                nzPos.push_back(i);
                nzDigit.push_back(d);
            }
        }

        int m = nzDigit.size();

        vector<long long> pow10(m + 1, 1);
        for (int i = 1; i <= m; i++)
            pow10[i] = (pow10[i - 1] * 10) % MOD;

        vector<long long> prefVal(m + 1, 0);
        for (int i = 0; i < m; i++)
            prefVal[i + 1] = (prefVal[i] * 10 + nzDigit[i]) % MOD;

        vector<int> ans;

        for (auto &q : queries) {
            int l = q[0], r = q[1];

            long long sum = prefSum[r + 1] - prefSum[l];

            auto it1 = lower_bound(nzPos.begin(), nzPos.end(), l);
            auto it2 = upper_bound(nzPos.begin(), nzPos.end(), r);

            if (it1 == it2) {
                ans.push_back(0);
                continue;
            }

            int L = it1 - nzPos.begin();
            int R = (it2 - nzPos.begin()) - 1;
            int len = R - L + 1;

            long long val =
                (prefVal[R + 1] - prefVal[L] * pow10[len] % MOD + MOD) % MOD;

            ans.push_back((val * (sum % MOD)) % MOD);
        }

        return ans;
    }
};