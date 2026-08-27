class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        // Try the rightmost possible position to make
        // the permutation greater than target.
        for (int i = n - 1; i >= 0; i--) {

            // Count all characters available in s
            vector<int> cnt(26, 0);

            for (char c : s) {
                cnt[c - 'a']++;
            }

            // Try to match target[0 ... i-1]
            bool possible = true;

            for (int j = 0; j < i; j++) {

                int x = target[j] - 'a';

                if (cnt[x] == 0) {
                    possible = false;
                    break;
                }

                cnt[x]--;
            }

            // Target prefix cannot be formed
            if (!possible)
                continue;

            // At position i, find the smallest character
            // strictly greater than target[i].
            int current = target[i] - 'a';

            for (int c = current + 1; c < 26; c++) {

                if (cnt[c] > 0) {

                    string ans = target.substr(0, i);

                    // Make answer greater here
                    ans += char('a' + c);

                    cnt[c]--;

                    // Put remaining characters
                    // in smallest possible order.
                    for (int x = 0; x < 26; x++) {
                        while (cnt[x] > 0) {
                            ans += char('a' + x);
                            cnt[x]--;
                        }
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};