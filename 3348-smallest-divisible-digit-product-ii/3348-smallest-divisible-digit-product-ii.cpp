#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int E2[10], E3[10], E5[10], E7[10];
    vector<vector<int>> minDig; // minDig[i][j]: min digits to get >= i (2-exp) and >= j (3-exp)
    int A, B;

    void buildDigitTables() {
        int e2[10] = {0,0,1,0,2,0,1,0,3,0};
        int e3[10] = {0,0,0,1,0,0,1,0,0,2};
        int e5[10] = {0,0,0,0,0,1,0,0,0,0};
        int e7[10] = {0,0,0,0,0,0,0,1,0,0};
        for (int i = 0; i < 10; i++) { E2[i]=e2[i]; E3[i]=e3[i]; E5[i]=e5[i]; E7[i]=e7[i]; }
    }

    void buildMinDigDP(int a, int b) {
        A = a; B = b;
        minDig.assign(A + 1, vector<int>(B + 1, INT_MAX / 2));
        minDig[0][0] = 0;
        vector<pair<int,int>> opts = {{1,0},{0,1},{2,0},{1,1},{3,0},{0,2}}; // digits 2,3,4,6,8,9
        for (int i = 0; i <= A; i++) {
            for (int j = 0; j <= B; j++) {
                if (i == 0 && j == 0) continue;
                int best = INT_MAX / 2;
                for (auto &pr : opts) {
                    int pi = max(0, i - pr.first);
                    int pj = max(0, j - pr.second);
                    if (pi == i && pj == j) continue; // no progress
                    best = min(best, minDig[pi][pj] + 1);
                }
                minDig[i][j] = best;
            }
        }
    }

    inline int getMinDig(int a, int b) {
        if (a < 0) a = 0; if (a > A) a = A;
        if (b < 0) b = 0; if (b > B) b = B;
        return minDig[a][b];
    }

    inline bool feasible(long long R, int a, int b, int c, int d) {
        if (a < 0) a = 0; if (b < 0) b = 0; if (c < 0) c = 0; if (d < 0) d = 0;
        long long need = (long long)c + d + getMinDig(a, b);
        return R >= need;
    }

    string buildSuffix(long long R, int a, int b, int c, int d) {
        string res;
        res.reserve((size_t)R);
        for (long long pos = 0; pos < R; pos++) {
            long long remPos = R - pos - 1;
            for (int v = 1; v <= 9; v++) {
                int na = a - E2[v], nb = b - E3[v], nc = c - E5[v], nd = d - E7[v];
                if (na < 0) na = 0; if (nb < 0) nb = 0;
                if (nc < 0) nc = 0; if (nd < 0) nd = 0;
                if (feasible(remPos, na, nb, nc, nd)) {
                    res.push_back(char('0' + v));
                    a = na; b = nb; c = nc; d = nd;
                    break;
                }
            }
        }
        return res;
    }

    string smallestNumber(string num, long long t) {
        buildDigitTables();

        int a = 0, b = 0, c = 0, d = 0;
        long long tt = t;
        while (tt % 2 == 0) { tt /= 2; a++; }
        while (tt % 3 == 0) { tt /= 3; b++; }
        while (tt % 5 == 0) { tt /= 5; c++; }
        while (tt % 7 == 0) { tt /= 7; d++; }
        if (tt != 1) return "-1";

        buildMinDigDP(a, b);

        int L = (int)num.size();
        vector<long long> pa(L + 1, 0), pb(L + 1, 0), pc(L + 1, 0), pd(L + 1, 0);
        int z = L; // first index of '0'
        for (int i = 0; i < L; i++) {
            int v = num[i] - '0';
            pa[i+1] = pa[i] + E2[v];
            pb[i+1] = pb[i] + E3[v];
            pc[i+1] = pc[i] + E5[v];
            pd[i+1] = pd[i] + E7[v];
            if (v == 0 && z == L) z = i;
        }

        // Case: num itself already works
        if (z == L) {
            if (pa[L] >= a && pb[L] >= b && pc[L] >= c && pd[L] >= d) {
                return num;
            }
        }

        int pmax = (z == L) ? (L - 1) : z;

        for (int p = pmax; p >= 0; p--) {
            int startV = (num[p] == '0') ? 1 : (num[p] - '0' + 1);
            if (startV > 9) continue;
            long long R = L - 1 - p;
            int pa_p = (int)pa[p], pb_p = (int)pb[p], pc_p = (int)pc[p], pd_p = (int)pd[p];
            for (int v = startV; v <= 9; v++) {
                int na = a - pa_p - E2[v];
                int nb = b - pb_p - E3[v];
                int nc = c - pc_p - E5[v];
                int nd = d - pd_p - E7[v];
                if (na < 0) na = 0; if (nb < 0) nb = 0;
                if (nc < 0) nc = 0; if (nd < 0) nd = 0;
                if (feasible(R, na, nb, nc, nd)) {
                    string suf = buildSuffix(R, na, nb, nc, nd);
                    return num.substr(0, p) + char('0' + v) + suf;
                }
            }
        }

        // Case: need an extra digit (longer number)
        long long M = (long long)c + d + getMinDig(a, b);
        long long Lp = max((long long)L + 1, M);
        return buildSuffix(Lp, a, b, c, d);
    }
};