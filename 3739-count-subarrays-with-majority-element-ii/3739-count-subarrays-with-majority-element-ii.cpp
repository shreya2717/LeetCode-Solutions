class Fenwick {
public:
    vector<int> bit;
    int n;

    Fenwick(int n) {
        this->n = n;
        bit.assign(n + 1, 0);
    }

    void update(int idx, int val) {
        while (idx <= n) {
            bit[idx] += val;
            idx += idx & (-idx);
        }
    }

    int query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += bit[idx];
            idx -= idx & (-idx);
        }
        return sum;
    }
};

class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();

        int offset = n + 2;
        Fenwick bit(2 * n + 5);

        long long ans = 0;
        int pref = 0;

        // Insert prefix sum = 0
        bit.update(pref + offset, 1);

        for (int x : nums) {
            if (x == target)
                pref++;
            else
                pref--;

            // Count previous prefix sums smaller than current
            ans += bit.query(pref + offset - 1);

            // Insert current prefix sum
            bit.update(pref + offset, 1);
        }

        return ans;
    }
};