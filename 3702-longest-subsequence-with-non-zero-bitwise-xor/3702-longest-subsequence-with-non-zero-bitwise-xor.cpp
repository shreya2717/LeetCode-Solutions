#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size();
        long long total = 0;
        bool hasNonZero = false;

        for (int x : nums) {
            total ^= x;
            if (x != 0) hasNonZero = true;
        }

        if (total != 0) return n;
        if (hasNonZero) return n - 1;
        return 0;
    }
};