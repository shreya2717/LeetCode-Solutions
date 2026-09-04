class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int mn = *min_element(nums1.begin(), nums1.end());

        // Minimum is odd:
        // every even number can subtract mn and become odd.
        if (mn % 2 == 1) {
            return true;
        }

        // Minimum is even:
        // therefore all numbers must already be even.
        for (int x : nums1) {
            if (x % 2 == 1) {
                return false;
            }
        }

        return true;
    }
};