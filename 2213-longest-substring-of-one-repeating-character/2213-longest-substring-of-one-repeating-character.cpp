class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int n = s.size();
        int k = queryCharacters.size();
        set<int> starts;        // run start indices
        map<int,int> startLen;  // start -> run length
        multiset<int> lens;

        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && s[j] == s[i]) j++;
            int length = j - i;
            starts.insert(i);
            startLen[i] = length;
            lens.insert(length);
            i = j;
        }

        auto findRunStart = [&](int idx) {
            auto it = starts.upper_bound(idx);
            --it;
            return *it;
        };
        auto removeRun = [&](int start) {
            lens.erase(lens.find(startLen[start]));
            startLen.erase(start);
            starts.erase(start);
        };
        auto addRun = [&](int start, int length) {
            starts.insert(start);
            startLen[start] = length;
            lens.insert(length);
        };

        vector<int> ans;
        ans.reserve(k);
        for (int q = 0; q < k; q++) {
            int idx = queryIndices[q];
            char c = queryCharacters[q];
            if (s[idx] == c) {
                ans.push_back(*lens.rbegin());
                continue;
            }

            int start = findRunStart(idx);
            int length = startLen[start];
            int end = start + length - 1;
            removeRun(start);
            if (start < idx) addRun(start, idx - start);
            if (idx < end)   addRun(idx + 1, end - idx);

            s[idx] = c;

            int newLeft = idx, newRight = idx;
            if (idx > 0 && s[idx - 1] == c) {
                int ls = findRunStart(idx - 1);
                int ll = startLen[ls];
                removeRun(ls);
                newLeft = ls;
                (void)ll;
            }
            if (idx + 1 < n && s[idx + 1] == c) {
                int rs = idx + 1; // guaranteed to be a run start after the split above
                int rl = startLen[rs];
                removeRun(rs);
                newRight = rs + rl - 1;
            }
            addRun(newLeft, newRight - newLeft + 1);

            ans.push_back(*lens.rbegin());
        }
        return ans;
    }
};