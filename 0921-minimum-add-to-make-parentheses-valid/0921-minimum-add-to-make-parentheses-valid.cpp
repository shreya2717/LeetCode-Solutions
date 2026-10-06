class Solution {
public:
    int minAddToMakeValid(string s) {
        int balance = 0;
        int ans = 0;

        for (char c : s) {
            if (c == '(') {
                balance++;
            } 
            else {
                if (balance > 0) {
                    balance--;
                } 
                else {
                    // Insert '(' before this ')'
                    ans++;
                }
            }
        }

        // Insert ')' for remaining '('
        ans += balance;

        return ans;
    }
};