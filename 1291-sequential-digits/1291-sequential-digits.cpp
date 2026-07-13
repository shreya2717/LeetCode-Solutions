class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> result;

        string digits = "123456789";

        // Generate all possible sequential digit numbers
        for (int len = 2; len <= 9; len++) {
            for (int start = 0; start + len <= 9; start++) {
                int num = stoi(digits.substr(start, len));

                if (num >= low && num <= high) {
                    result.push_back(num);
                }
            }
        }

        sort(result.begin(), result.end());
        return result;
    }
};