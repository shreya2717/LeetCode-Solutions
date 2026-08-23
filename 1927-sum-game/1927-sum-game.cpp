class Solution {
public:
    bool sumGame(string num) {
        int n = num.size(), half = n / 2;
        long long sumA = 0, sumB = 0;
        int cntA = 0, cntB = 0;
        
        for (int i = 0; i < half; i++) {
            if (num[i] == '?') cntA++;
            else sumA += num[i] - '0';
        }
        for (int i = half; i < n; i++) {
            if (num[i] == '?') cntB++;
            else sumB += num[i] - '0';
        }
        
        long long diff = sumA - sumB;
        int totalQ = cntA + cntB;
        
        // Odd number of '?' -> Alice moves last, she always wins
        if (totalQ % 2 == 1) return true;
        
        // Even case: Bob can force this diff via mirroring strategy
        diff += 9LL * (cntA - cntB) / 2;
        
        return diff != 0;
    }
};