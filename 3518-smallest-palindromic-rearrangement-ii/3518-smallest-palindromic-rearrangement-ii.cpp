class Solution {
public:
    static const long long LIM = 1000001;

    long long C(int n, int r) {
        if (r > n) return 0;
        r = min(r, n - r);

        long long ans = 1;
        for (int i = 1; i <= r; i++) {
            ans = ans * (n - r + i) / i;
            if (ans >= LIM) return LIM;
        }
        return ans;
    }

    long long countWays(vector<int>& half) {
        int total = 0;
        for (int x : half) total += x;

        long long ways = 1;
        int rem = total;

        for (int x : half) {
            if (x == 0) continue;

            long long comb = C(rem, x);

            if (ways >= LIM || comb >= LIM) {
                ways = LIM;
            } else {
                ways *= comb;
                if (ways > LIM) ways = LIM;
            }

            rem -= x;
        }

        return ways;
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        vector<int> half(26, 0);
        string mid = "";

        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            if (freq[i] % 2)
                mid.push_back(char('a' + i));
        }

        long long ways = countWays(half);

        if (ways < k)
            return "";

        string left = "";
        int rem = 0;
        for (int x : half) rem += x;

        while (rem > 0) {
            for (int c = 0; c < 26; c++) {
                if (half[c] == 0) continue;

                half[c]--;

                long long cur = countWays(half);

                if (cur >= k) {
                    left.push_back(char('a' + c));
                    rem--;
                    break;
                } else {
                    k -= cur;
                    half[c]++;
                }
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        return left + mid + right;
    }
};