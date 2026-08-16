class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {0};

        for (int x : stones) {
            cnt[x % 3]++;
        }

        // No multiples of 3
        if (cnt[0] % 2 == 0) {
            return cnt[1] > 0 && cnt[2] > 0;
        }

        // Odd number of multiples of 3
        return abs(cnt[1] - cnt[2]) > 2;
    }
};