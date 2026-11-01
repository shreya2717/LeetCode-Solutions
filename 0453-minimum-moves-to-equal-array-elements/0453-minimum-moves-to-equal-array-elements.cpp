class Solution {
public:
    int minMoves(vector<int>& nums) {
        int mn = *min_element(nums.begin(), nums.end());
        int sum = accumulate(nums.begin(), nums.end(), 0LL);

        return sum - 1LL * nums.size() * mn;
    }
};