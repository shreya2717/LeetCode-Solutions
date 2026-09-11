class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int count[10] = {};

        // Count frequency of each digit
        for (int digit : digits) {
            count[digit]++;
        }

        int ans = 0;

        // Check every 3-digit number
        for (int num = 100; num <= 999; num++) {

            // Number must be even
            if (num % 2 != 0)
                continue;

            int a = num / 100;
            int b = (num / 10) % 10;
            int c = num % 10;

            int needed[10] = {};

            needed[a]++;
            needed[b]++;
            needed[c]++;

            bool possible = true;

            // Check if we have enough copies
            for (int d = 0; d <= 9; d++) {
                if (needed[d] > count[d]) {
                    possible = false;
                    break;
                }
            }

            if (possible)
                ans++;
        }

        return ans;
    }
};