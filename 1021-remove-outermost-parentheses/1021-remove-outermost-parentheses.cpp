class Solution {
public:
    string removeOuterParentheses(string s) {
        string ans;
        int depth = 0;

        for (char c : s) {

            if (c == '(') {
                // Don't add the outermost '('
                if (depth > 0)
                    ans += c;

                depth++;
            }
            else {
                depth--;

                // Don't add the outermost ')'
                if (depth > 0)
                    ans += c;
            }
        }

        return ans;
    }
};