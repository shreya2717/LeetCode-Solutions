class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // suf[j] = position of word2[j] in a lexicographically
        // latest exact subsequence of word2[j...m-1]
        vector<int> suf(m + 1, -1);

        suf[m] = n;

        int p = n - 1;

        for (int j = m - 1; j >= 0; j--) {
            while (p >= 0 && word1[p] != word2[j]) {
                p--;
            }

            if (p < 0) {
                suf[j] = -1;
            } else {
                suf[j] = p;
                p--;
            }
        }

        vector<int> ans;

        int prev = -1;
        bool changed = false;

        for (int j = 0; j < m; j++) {
            bool found = false;

            for (int i = prev + 1; i < n; i++) {

                // Case 1: Exact match.
                // We can still use the one mismatch later.
                if (word1[i] == word2[j]) {
                    ans.push_back(i);
                    prev = i;
                    found = true;
                    break;
                }

                // Case 2: Use our one allowed mismatch here.
                // The remaining part must match exactly.
                if (!changed && i < suf[j + 1]) {
                    ans.push_back(i);
                    prev = i;
                    changed = true;
                    found = true;
                    break;
                }
            }

            if (!found) {
                return {};
            }
        }

        return ans;
    }
};