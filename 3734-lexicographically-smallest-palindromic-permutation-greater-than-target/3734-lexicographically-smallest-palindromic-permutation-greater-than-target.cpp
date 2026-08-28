class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        int cnt[26] = {0};
        for (char c : s) cnt[c - 'a']++;

        int oddCnt = 0, oddChar = -1;
        for (int c = 0; c < 26; c++)
            if (cnt[c] & 1) { oddCnt++; oddChar = c; }

        // s must be able to form SOME palindrome
        if ((n % 2 == 0 && oddCnt != 0) || (n % 2 == 1 && oddCnt != 1)) return "";

        int freeLen = n / 2;          // freely permutable half-positions
        int h = (n + 1) / 2;          // half length incl. middle char if n is odd
        bool odd = (n % 2 == 1);
        int midChar = odd ? oddChar : -1;

        int avail[26];
        for (int c = 0; c < 26; c++) avail[c] = cnt[c] / 2;

        string targetHalf = target.substr(0, h);

        // build the full palindrome from a chosen half string
        auto buildFull = [&](const string& half) {
            string full = half;
            int start = odd ? h - 2 : h - 1;
            for (int i = start; i >= 0; i--) full += half[i];
            return full;
        };

        // try to consume targetHalf[0..upto-1] from a fresh copy of avail
        auto simulate = [&](int upto, int outAvail[26]) -> bool {
            for (int c = 0; c < 26; c++) outAvail[c] = avail[c];
            for (int j = 0; j < upto; j++) {
                if (j < freeLen) {
                    int c = targetHalf[j] - 'a';
                    if (outAvail[c] <= 0) return false;
                    outAvail[c]--;
                } else {                       // forced middle slot
                    if (targetHalf[j] - 'a' != midChar) return false;
                }
            }
            return true;
        };

        // k = longest prefix of targetHalf that is actually achievable
        int k = 0;
        {
            int tmp[26];
            for (int i = 0; i <= h; i++) {
                if (simulate(i, tmp)) k = i; else break;
            }
        }

        // Best case: half can equal targetHalf exactly
        if (k == h) {
            string full = buildFull(targetHalf);
            if (full > target) return full;
        }

        // Otherwise, find the rightmost position where we can diverge upward
        int startI = min(k, h - 1);
        for (int i = startI; i >= 0; i--) {
            int st[26];
            if (!simulate(i, st)) continue;

            if (i < freeLen) {                 // free position
                int tc = targetHalf[i] - 'a';
                int chosen = -1;
                for (int c = tc + 1; c < 26; c++)
                    if (st[c] > 0) { chosen = c; break; }
                if (chosen == -1) continue;

                st[chosen]--;
                string half = targetHalf.substr(0, i);
                half += char('a' + chosen);
                for (int c = 0; c < 26; c++)   // fill the rest ascending
                    while (st[c] > 0 && (int)half.size() < freeLen) {
                        half += char('a' + c);
                        st[c]--;
                    }
                if (odd) half += char('a' + midChar);
                return buildFull(half);
            } else {                           // i == freeLen, forced middle slot
                int tc = targetHalf[i] - 'a';
                if (midChar > tc) {
                    string half = targetHalf.substr(0, i);
                    half += char('a' + midChar);
                    return buildFull(half);
                }
            }
        }

        return "";
    }
};