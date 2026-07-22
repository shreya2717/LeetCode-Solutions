class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.size();
        vector<int> runStart, runEnd; vector<char> runChar;
        {
            int i = 0;
            while (i < n) {
                int j = i;
                while (j < n && s[j] == s[i]) j++;
                runStart.push_back(i);
                runEnd.push_back(j - 1);
                runChar.push_back(s[i]);
                i = j;
            }
        }
        int m = runStart.size();
        vector<long long> runLen(m);
        for (int k = 0; k < m; k++) runLen[k] = runEnd[k] - runStart[k] + 1;

        vector<int> posRun(n);
        for (int k = 0; k < m; k++)
            for (int p = runStart[k]; p <= runEnd[k]; p++) posRun[p] = k;

        long long totalOnes = 0;
        for (char c : s) if (c == '1') totalOnes++;

        // g[idx]: gain from removing run idx (a '1'-run) and merging its
        // neighboring '0'-runs into one, then turning them all back to '1'.
        vector<long long> g(max(m,1), -1);
        for (int idx = 1; idx < m - 1; idx++)
            if (runChar[idx] == '1') g[idx] = runLen[idx - 1] + runLen[idx + 1];

        int LOG = 1;
        while ((1 << LOG) <= max(m,1)) LOG++;
        vector<vector<long long>> sp(LOG, vector<long long>(max(m,1), -1));
        if (m > 0) sp[0] = g;
        for (int j = 1; j < LOG; j++) {
            int half = 1 << (j - 1);
            for (int i = 0; i + (1 << j) <= m; i++)
                sp[j][i] = max(sp[j - 1][i], sp[j - 1][i + half]);
        }
        vector<int> logt(m + 1, 0);
        for (int i = 2; i <= m; i++) logt[i] = logt[i / 2] + 1;

        auto rangeMax = [&](int l, int r) -> long long {
            if (l > r) return -1;
            int j = logt[r - l + 1];
            return max(sp[j][l], sp[j][r - (1 << j) + 1]);
        };

        vector<int> ans;
        ans.reserve(queries.size());
        for (auto &q : queries) {
            int l = q[0], r = q[1];
            int a = posRun[l], b = posRun[r];
            long long best = 0;

            if (a != b) {
                int gap = b - a;
                long long truncA = runEnd[a] - l + 1;   // truncated length of boundary run a
                long long truncB = r - runStart[b] + 1; // truncated length of boundary run b

                if (gap == 1) {
                    // no run strictly between a and b -> no trade possible
                } else if (gap == 2) {
                    int idx = a + 1; // the only run strictly between
                    if (runChar[idx] == '1') best = truncA + truncB;
                } else {
                    if (runChar[a + 1] == '1')
                        best = max(best, truncA + runLen[a + 2]);
                    if (runChar[b - 1] == '1')
                        best = max(best, runLen[b - 2] + truncB);
                    if (a + 2 <= b - 2) {
                        long long mx = rangeMax(a + 2, b - 2);
                        if (mx > 0) best = max(best, mx);
                    }
                }
            }
            ans.push_back((int)(totalOnes + best));
        }
        return ans;
    }
};